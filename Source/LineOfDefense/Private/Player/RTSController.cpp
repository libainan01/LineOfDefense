// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/RTSController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Actor/ConstructionSide.h"
#include "ActorComponent/CommandController.h"
#include "Interaction/RTSActorInterface.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

ARTSController::ARTSController()
{
	bReplicates = true;//开启网络同步
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

	//初始化输入回调函数
	LeftButtonStarted = &ARTSController::BeginDrawTraceBox;
	LeftButtonTriggered = &ARTSController::DrawTraceBox;
	LeftButtonEnd = &ARTSController::FinishDrawTraceBox;
}

void ARTSController::SetupInputComponent()
{
	Super::SetupInputComponent();
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(MouseLeftButtonAction,ETriggerEvent::Started,this,&ARTSController::OnLeftButtonStarted);
	EnhancedInputComponent->BindAction(MouseLeftButtonAction,ETriggerEvent::Triggered,this,&ARTSController::OnLeftButtonTriggered);
	EnhancedInputComponent->BindAction(MouseLeftButtonAction,ETriggerEvent::Completed,this,&ARTSController::OnLeftButtonEnd);
	EnhancedInputComponent->BindAction(MouseRightButtonAction,ETriggerEvent::Started,this,&ARTSController::RightButtonClick);
	
}

FHitResult ARTSController::GetCursorHitResult()
{
	FHitResult CurseHitResult;
	GetHitResultUnderCursor(ECC_Visibility,false,CurseHitResult);
	return CurseHitResult;
}

void ARTSController::ReviewConstructionApplication(FConstructionInfo NewCosntructionInfo)
{
	check(ConstructionSideClass);
	
	LeftButtonEnd = &ARTSController::ApproveConstructionApplication;
	
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	FVector Location = GetCursorHitResult().Location;
	ConstructionSide = GetWorld()->SpawnActor<AConstructionSide>(ConstructionSideClass,Location,FRotator::ZeroRotator,SpawnParameters);
    
	GetWorld()->GetTimerManager().SetTimer(ConstructionReviewTimerHandle,this,&ARTSController::CheckConstruction,0.2f,true);
}

void ARTSController::CheckConstruction()
{
	FVector Location = GetCursorHitResult().Location;
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
	for (auto Actor : ThisActors)
	{
		Actor->GetCommandController()->SetCommandInfo(NewCommandInfo,bIsPreset);
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
	GetHitResultUnderCursor(ECC_Visibility,false,CurseHitResult);
	RightButtonClickResult.Location = CurseHitResult.Location;
	RightButtonClickResult.Target = CurseHitResult.GetActor();

	MakeCommandInfo(RightButtonClickResult);
	
}

void ARTSController::RightButtonRelease(const FInputActionValue& InputActionValue)
{
	
}

void ARTSController::BeginDrawTraceBox()
{
	FHitResult CursorHitResult;
	GetHitResultUnderCursor(ECC_Visibility,false,CursorHitResult);
	StartTracepoint = CursorHitResult.Location;	
}

void ARTSController::DrawTraceBox()
{
	FHitResult CursorHitResult;
	GetHitResultUnderCursor(ECC_Visibility,false,CursorHitResult);
	FVector Diagonal = CursorHitResult.Location - StartTracepoint;

	FVector StartPoint = FVector(StartTracepoint.X,StartTracepoint.Y+UKismetMathLibrary::SafeDivide(Diagonal.Y,2),0);
	FVector EndPoint = FVector(CursorHitResult.Location.X,StartTracepoint.Y+UKismetMathLibrary::SafeDivide(Diagonal.Y,2),0);
	FVector HalfSize = FVector(0,UKismetMathLibrary::SafeDivide(Diagonal.Y,2),500);
	TArray<AActor*> IgnoreActors;
	UKismetSystemLibrary::BoxTraceMulti(GetWorld(),StartPoint,EndPoint,HalfSize,FRotator(0,0,0),TraceTypeQuery3,false,IgnoreActors,EDrawDebugTrace::ForOneFrame,TraceBoxHitResults,true);
}

void ARTSController::FinishDrawTraceBox()
{
	if (TraceBoxHitResults.IsEmpty())
	{
		return;
	}
	for (auto BoxHitResult : TraceBoxHitResults )
	{
		TScriptInterface<IRTSActorInterface> BoxHitActor = BoxHitResult.GetActor();
		if(!BoxHitActor) continue;
		BoxHitActor->HightLightActor();

		ThisActors.Add(BoxHitResult.GetActor());
	}

	for (auto LastHitActor :LastActors)
	{
		if (!LastHitActor) continue;

		LastHitActor->UnHightLightActor();
	}
}

