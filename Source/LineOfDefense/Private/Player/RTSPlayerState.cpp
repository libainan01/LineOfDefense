// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/RTSPlayerState.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/RTSAbilitySystemComponent.h"
#include "AbilitySystem/RTSAttributeSet.h"
#include "ActorComponent/RTSMaterialsBackpack.h"

ARTSPlayerState::ARTSPlayerState()
{
	NetUpdateFrequency = 100.0f;

	RTSAbilitySystemComponent = CreateDefaultSubobject<URTSAbilitySystemComponent>(TEXT("AsbilitySystemComponent"));
	RTSAbilitySystemComponent->SetIsReplicated(true);
	RTSAbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	RTSAttributes = CreateDefaultSubobject<URTSAttributeSet>(TEXT("RTSAttributeSet"));

	Backpack = CreateDefaultSubobject<URTSMaterialsBackpack>(TEXT("Backpack"));
}

UAbilitySystemComponent* ARTSPlayerState::GetAbilitySystemComponent() const
{
	return RTSAbilitySystemComponent;
}

void ARTSPlayerState::SaveActor(FRTSActorInfo TargetActor, ERTSActorType ActorType)
{
	switch (ActorType)
	{
	case ERTSActorType::Worker:
		WorkerArray.Add(TargetActor);
		break;
	case ERTSActorType::Barracks:
		BarracksArray.Add(TargetActor);
		break;
	case ERTSActorType::WareHouse:
		WareHouseArray.Add(TargetActor);
		break;
	case ERTSActorType::Material:
		MaterialArray.Add(TargetActor);
		break;
		default:;
	}
}

TArray<FRTSActorInfo> ARTSPlayerState::GetActor(ERTSActorType ActorType)
{
	switch (ActorType)
	{
	case ERTSActorType::Worker:
		return WorkerArray;
	case ERTSActorType::Barracks:
		return BarracksArray;
	case ERTSActorType::WareHouse:
		return WareHouseArray;
	case ERTSActorType::Material:
		return MaterialArray;
	default:
		TArray<FRTSActorInfo> Actors;
		return Actors;
	}
}

void ARTSPlayerState::UpdateRTSMaterialInAttributes()const
{
	TObjectPtr<URTSAttributeSet> AS = Cast<URTSAttributeSet>(RTSAttributes);
	AS->SetGold(Backpack->GetStoringRTSMaterials().GetGold());
	AS->SetWood(Backpack->GetStoringRTSMaterials().GetWood());
}

