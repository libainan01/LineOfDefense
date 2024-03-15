// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/RTSController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
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
	check(Subsystem);
	Subsystem->AddMappingContext(RTSContext,0);

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void ARTSController::SetupInputComponent()
{
	Super::SetupInputComponent();
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(MouseLeftButtonAction,ETriggerEvent::Started,this,&ARTSController::BeginDrawTraceBox);
	EnhancedInputComponent->BindAction(MouseLeftButtonAction,ETriggerEvent::Triggered,this,&ARTSController::DrawTraceBox);
	EnhancedInputComponent->BindAction(MouseLeftButtonAction,ETriggerEvent::Completed,this,&ARTSController::FinishDrawTraceBox);
}

void ARTSController::BeginDrawTraceBox(const FInputActionValue& InputActionValue)
{
	FHitResult CursorHitResult;
	GetHitResultUnderCursor(ECC_Visibility,false,CursorHitResult);
	StartTracepoint = CursorHitResult.Location;
}

void ARTSController::DrawTraceBox(const FInputActionValue& InputActionValue)
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

void ARTSController::FinishDrawTraceBox(const FInputActionValue& InputActionValue)
{
	for (auto BoxHitResult : TraceBoxHitResults )
	{
		IRTSActorInterface* BoxHitActor = Cast<IRTSActorInterface>(BoxHitResult.GetActor());
		if(!BoxHitActor) continue;
		BoxHitActor->HightLightActor();

		ThisActors.Add(BoxHitActor);
	}

	for (auto LastHitActor :LastActors)
	{
		if (!LastHitActor) continue;

		LastHitActor->UnHightLightActor();
	}
	
}
