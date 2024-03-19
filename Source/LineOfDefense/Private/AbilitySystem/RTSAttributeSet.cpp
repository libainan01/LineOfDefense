// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/RTSAttributeSet.h"
#include "Net/UnrealNetwork.h"

URTSAttributeSet::URTSAttributeSet()
{
	InitHealth(100.f);
}

void URTSAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME_CONDITION_NOTIFY(URTSAttributeSet,Health,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(URTSAttributeSet,MaxHealth,COND_None,REPNOTIFY_Always);
}

void URTSAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URTSAttributeSet,Health,OldHealth);
}

void URTSAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URTSAttributeSet,MaxHealth,OldMaxHealth);
}
