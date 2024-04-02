// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/RTSPlayerState.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/RTSAbilitySystemComponent.h"
#include "AbilitySystem/RTSAttributeSet.h"

ARTSPlayerState::ARTSPlayerState()
{
	NetUpdateFrequency = 100.0f;

	RTSAbilitySystemComponent = CreateDefaultSubobject<URTSAbilitySystemComponent>(TEXT("AsbilitySystemComponent"));
	RTSAbilitySystemComponent->SetIsReplicated(true);
	RTSAbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	RTSAttributes = CreateDefaultSubobject<URTSAttributeSet>(TEXT("RTSAttributeSet"));
}

UAbilitySystemComponent* ARTSPlayerState::GetAbilitySystemComponent() const
{
	return RTSAbilitySystemComponent;
}

void ARTSPlayerState::SaveActor(AActor* TargetActor, ERTSActorType ActorType)
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

TArray<AActor*> ARTSPlayerState::GetActor(ERTSActorType ActorType)
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
		TArray<AActor*> Actors;
		return Actors;
	}
}
