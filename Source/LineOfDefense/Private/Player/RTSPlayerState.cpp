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
