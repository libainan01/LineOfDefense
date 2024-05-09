// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/RTSController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Actor/ConstructionSide.h"
#include "ActorComponent/CommandController.h"
#include "Interaction/RTSActorInterface.h"
#include "Player/RTSPlayerState.h"

#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

ARTSController::ARTSController()
{
	bReplicates = true;//开启网络同步

	//初始化输入回调函数
	LeftButtonStarted = &ARTSController::BeginDrawTraceBox;
	LeftButtonTriggered = &ARTSController::DrawTraceBox;
	LeftButtonEnd = &ARTSController::FinishDrawTraceBox;
	LeftShiftStarted = &ARTSController::SetPresetCommand;
	LeftShiftEnd = &ARTSController::CancelPresetCommand;
}

void ARTSController::BeginPlay()
{
	Super::BeginPlay();
	check(RTSContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if(Subsystem)
	{
	    Subsystem->AddMappingContext(RTSContext,0);
	}

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);

	ConstructionApplicationRequest.BindDynamic(this,&ARTSController::ReviewConstructionApplication);
	
}

void ARTSController::SetupInputComponent()
{
	Super::SetupInputComponent();
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(MouseLeftButtonAction,ETriggerEvent::Started,this,&ARTSController::OnLeftButtonStarted);
	EnhancedInputComponent->BindAction(MouseLeftButtonAction,ETriggerEvent::Triggered,this,&ARTSController::OnLeftButtonTriggered);
	EnhancedInputComponent->BindAction(MouseLeftButtonAction,ETriggerEvent::Completed,this,&ARTSController::OnLeftButtonEnd);
	EnhancedInputComponent->BindAction(MouseRightButtonAction,ETriggerEvent::Started,this,&ARTSController::RightButtonClick);
	EnhancedInputComponent->BindAction(LeftShiftClick,ETriggerEvent::Started,this,&ARTSController::OnLeftShiftStarted);
	EnhancedInputComponent->BindAction(LeftShiftClick,ETriggerEvent::Completed,this,&ARTSController::CancelPresetCommand);
	
}

FHitResult ARTSController::GetCursorHitResult(ECollisionChannel CollisionChannel)
{
	FHitResult CurseHitResult;
	GetHitResultUnderCursor(CollisionChannel,false,CurseHitResult);
	return CurseHitResult;
}

void ARTSController::ReviewConstructionApplication(FConstructionInfo NewCosntructionInfo)
{
	check(ConstructionSideClass);
	
	LeftButtonEnd = &ARTSController::ApproveConstructionApplication;
	
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	FVector Location = GetCursorHitResult(ECC_GameTraceChannel2).Location;
	ConstructionSide = GetWorld()->SpawnActor<AConstructionSide>(ConstructionSideClass,Location,FRotator::ZeroRotator,SpawnParameters);
    ConstructionSide->InitialConstructionSide(NewCosntructionInfo,GetPlayerState<ARTSPlayerState>());
	
	GetWorld()->GetTimerManager().SetTimer(ConstructionReviewTimerHandle,this,&ARTSController::CheckConstruction,0.2f,true);
}

void ARTSController::CheckConstruction()
{
	FVector Location = GetCursorHitResult(ECC_GameTraceChannel2).Location;
	ConstructionSide->SetActorLocation(Location);
}

void ARTSController::ApproveConstructionApplication()
{
	GetWorld()->GetTimerManager().ClearTimer(ConstructionReviewTimerHandle);
	if (ConstructionApplicationSignature.IsBound())
	{
		ConstructionApplicationSignature.Execute(true);//暂时没有建造检测
	}
	FCommandInfo CommandInfo;
	CommandInfo.SetConstructionSide(ConstructionSide);
	MakeCommandInfo(CommandInfo);
	LeftButtonEnd = &ARTSController::FinishDrawTraceBox;
}

void ARTSController::MakeCommandInfo(FCommandInfo NewCommandInfo)
{
	for (const auto Actor : ThisActors)
	{
		if(Actor->GetCommandController())
		{
			Actor->GetCommandController()->SetCommandInfo(NewCommandInfo,bIsPreset);
		}
	}
}

void ARTSController::OnLeftButtonStarted(const FInputActionValue& InputActionValue)
{
    (this->*LeftButtonStarted)();
}

void ARTSController::OnLeftButtonTriggered(const FInputActionValue& InputActionValue)
{
    (this->*LeftButtonTriggered)();
}

void ARTSController::OnLeftButtonEnd(const FInputActionValue& InputActionValue)
{
	(this->*LeftButtonEnd)();
}

void ARTSController::RightButtonClick(const FInputActionValue& InputActionValue)
{
	if (ThisActors.IsEmpty())
	{
		return;
	}
	
	FHitResult CurseHitResult;
	FCommandInfo RightButtonClickResult;
	CurseHitResult = GetCursorHitResult(ECC_Visibility);
	RightButtonClickResult.Location = CurseHitResult.Location;
	RightButtonClickResult.Target = CurseHitResult.GetActor();

	MakeCommandInfo(RightButtonClickResult);
	
}

void ARTSController::RightButtonRelease(const FInputActionValue& InputActionValue)
{
	
}
void ARTSController::OnLeftShiftStarted(const FInputActionValue& InputActionValue)
{
	(this->*LeftShiftStarted)();
}

void ARTSController::OnLeftShiftEnd(const FInputActionValue& InputActionValue)
{
	(this->*LeftShiftEnd)();
}

void ARTSController::BeginDrawTraceBox()
{
	FHitResult CursorHitResult;
	CursorHitResult = GetCursorHitResult(ECC_GameTraceChannel2);
	StartTracepoint = CursorHitResult.Location;	
}

void ARTSController::DrawTraceBox()
{
	FHitResult CursorHitResult;
	CursorHitResult = GetCursorHitResult(ECC_GameTraceChannel2);
	FVector Diagonal = CursorHitResult.Location - StartTracepoint;

	FVector StartPoint = FVector(StartTracepoint.X,StartTracepoint.Y+UKismetMathLibrary::SafeDivide(Diagonal.Y,2),0);
	FVector EndPoint = FVector(CursorHitResult.Location.X,StartTracepoint.Y+UKismetMathLibrary::SafeDivide(Diagonal.Y,2),0);
	FVector HalfSize = FVector(0,UKismetMathLibrary::SafeDivide(Diagonal.Y,2),1000);
	TArray<AActor*> IgnoreActors;
	IgnoreActors.Add(this);
	UKismetSystemLibrary::BoxTraceMulti(GetWorld(),StartPoint,EndPoint,HalfSize,FRotator(0,0,0),TraceTypeQuery4,false,IgnoreActors,EDrawDebugTrace::ForOneFrame,TraceBoxHitResults,true);
}

void ARTSController::FinishDrawTraceBox()
{
	ThisActors.Empty();
	
	if (!TraceBoxHitResults.IsEmpty())
	{
		for (auto BoxHitResult : TraceBoxHitResults )
		{
			TScriptInterface<IRTSActorInterface> BoxHitActor = BoxHitResult.GetActor();
			if(!BoxHitActor) continue;
			BoxHitActor->HightLightActor();

			ThisActors.AddUnique(BoxHitResult.GetActor());
		}
	}


	for (auto LastHitActor :LastActors)
	{
		if (!LastHitActor) continue;
		LastHitActor->UnHightLightActor();
	}
	
	LastActors = ThisActors;
	
	if (SelectActorRequest.IsBound())
	{
	    SelectActorRequest.Execute(ThisActors);
	}
	
}

void ARTSController::SetPresetCommand()
{
	bIsPreset = true;
}

void ARTSController::CancelPresetCommand()
{
	bIsPreset = false;
}

