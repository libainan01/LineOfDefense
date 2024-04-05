// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/RTSAttributeSet.h"
#include "Net/UnrealNetwork.h"

URTSAttributeSet::URTSAttributeSet()
{
	InitHealth(100.f);
	InitMaxHealth(100.f);
	InitWood(100);
	InitGold(50);
}

void URTSAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//设置网络同步条件
	DOREPLIFETIME_CONDITION_NOTIFY(URTSAttributeSet,Health,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(URTSAttributeSet,MaxHealth,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(URTSAttributeSet,Wood,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(URTSAttributeSet,Gold,COND_None,REPNOTIFY_Always);
}

void URTSAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URTSAttributeSet,Health,OldHealth);
}

void URTSAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URTSAttributeSet,MaxHealth,OldMaxHealth);
}

void URTSAttributeSet::OnRep_Wood(const FGameplayAttributeData& OldWood) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URTSAttributeSet,Wood,OldWood);
}

void URTSAttributeSet::OnRep_Gold(const FGameplayAttributeData& OldGold) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URTSAttributeSet,Gold,OldGold);
}

void URTSAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
}
