// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AI/RTSAIController.h"

#include "BehaviorTree/BehaviorTree.h"
#include "Character/RTSAIBase.h"

ARTSAIController::ARTSAIController()
{

}

void ARTSAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ARTSAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
    AIBase = Cast<ARTSAIBase>(InPawn);
}
