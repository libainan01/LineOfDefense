// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Interaction/RTSActorInterface.h"
#include "RTSAIController.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMonitorActorStates,ERTSActorStates,NewActorType);

UCLASS()
class LINEOFDEFENSE_API ARTSAIController : public AAIController
{
	GENERATED_BODY()
public:
	ARTSAIController();
	UPROPERTY(BlueprintAssignable)
	FMonitorActorStates MonitorActorStates;

protected:
	virtual void BeginPlay() override;
};
