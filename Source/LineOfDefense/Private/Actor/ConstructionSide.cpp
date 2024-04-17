// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/ConstructionSide.h"

#include "ActorComponent/RTSMaterialsBackpack.h"
#include "Character/RTSAIBase.h"
#include "Kismet/GameplayStatics.h"
#include "Player/RTSPlayerState.h"

float AConstructionSide::Building(int32 ConstructionEfficiency)
{
	ConstructionProgress += ConstructionEfficiency;
	float Progress ;
	if (ConstructionInfo.ConstructionTime == 0)
	{
		Progress = 1;
		return Progress;
	}
	Progress = ConstructionProgress/ConstructionInfo.ConstructionTime;
	if (Progress>=1)
	{
		FinishBuilding();
	}
	return Progress;
}

void AConstructionSide::SetConstructionInfo(FConstructionInfo NewConstructionInfo)
{
	ConstructionInfo = NewConstructionInfo;
}

void AConstructionSide::InitialConstructionSide(FConstructionInfo NewConstructionInfo, ARTSPlayerState* PS)
{
	ConstructionInfo = NewConstructionInfo;
	PlayerState = PS;
}

void AConstructionSide::BeginPlay()
{
	Super::BeginPlay();
	PlayerState = Cast<ARTSPlayerState>(UGameplayStatics::GetPlayerState(GetWorld(),0));
}

void AConstructionSide::ConsumableMaterials(FRTSMaterials ConsumableMaterials) const
{
	check(PlayerState)
	PlayerState->GetRTSMaterialsBackpack()->ConsumableRTSMaterials(ConsumableMaterials);
}

void AConstructionSide::FinishBuilding()
{
	FActorSpawnParameters ActorSpawnParameters;
	ActorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	GetWorld()->SpawnActor<ARTSAIBase>(ConstructionInfo.BlueprintClass,GetActorLocation(),GetActorRotation(),ActorSpawnParameters);
	this->Destroy();
}
