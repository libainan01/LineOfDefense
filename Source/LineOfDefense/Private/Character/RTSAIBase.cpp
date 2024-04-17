// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/RTSAIBase.h"

#include "AbilitySystem/RTSAttributeSet.h"
#include "ActorComponent/CommandController.h"
#include "Kismet/GameplayStatics.h"
#include "Player/RTSPlayerState.h"
#include "Player/AI/RTSAIController.h"

// Sets default values
ARTSAIBase::ARTSAIBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = ARTSAIController::StaticClass();
	CommandController = CreateDefaultSubobject<UCommandController>("CommandController");
}

ARTSAIBase::~ARTSAIBase()
{
	FRTSActorInfo RTSActorInfo(GetActorLocation(),this);
	Cast<ARTSPlayerState>(UGameplayStatics::GetPlayerState(GetWorld(),0))->DeleteActor(RTSActorInfo,Actortype);
}

void ARTSAIBase::HightLightActor()
{
	bHightlighted = true;
}

void ARTSAIBase::UnHightLightActor()
{
	bHightlighted = false;
}

void ARTSAIBase::SetActorState(ERTSActorStates NewActorStates)
{
	ActorStates = NewActorStates;
}

UBuildingTool* ARTSAIBase::GetBuildingTool() const
{
    if (BuildingTool!= nullptr)
    {
	    return BuildingTool;
    }
	return nullptr;
}

ARTSAIController* ARTSAIBase::GetRTSAIController() const
{
	return AIController;
}

FRTSMaterials ARTSAIBase::SetActorValue(FRTSMaterials NewMaterials)
{
	ActorValue = NewMaterials;
	return ActorValue;
}

// Called when the game starts or when spawned
void ARTSAIBase::BeginPlay()
{
	Super::BeginPlay();
	RTSAbilitySystemComponent->InitAbilityActorInfo(this,this);
	FRTSActorInfo RTSActorInfo(GetActorLocation(),this);
	AIController = GetController<ARTSAIController>();
    Cast<ARTSPlayerState>(UGameplayStatics::GetPlayerState(GetWorld(),0))->SaveActor(RTSActorInfo,Actortype);
}



