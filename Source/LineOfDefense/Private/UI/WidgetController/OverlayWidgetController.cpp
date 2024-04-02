// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/RTSAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	const URTSAttributeSet* RTSAttributes = CastChecked<URTSAttributeSet>(AttributeSet);

	OnHealthChanged.Broadcast(RTSAttributes->GetHealth());
	OnMaxHealthChanged.Broadcast(RTSAttributes->GetMaxHealth());
	OnWoodChanged.Broadcast(RTSAttributes->GetWood());
	OnGoldChanged.Broadcast(RTSAttributes->GetGold());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	const URTSAttributeSet* RTSAttributeSet = CastChecked<URTSAttributeSet>(AttributeSet);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(RTSAttributeSet->GetHealthAttribute()).AddUObject(this,&UOverlayWidgetController::HealthChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(RTSAttributeSet->GetMaxHealthAttribute()).AddUObject(this,&UOverlayWidgetController::MaxHealthChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(RTSAttributeSet->GetWoodAttribute()).AddUObject(this,&UOverlayWidgetController::WoodChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(RTSAttributeSet->GetGoldAttribute()).AddUObject(this,&UOverlayWidgetController::GoldChanged);
}

void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
{
    OnHealthChanged.Broadcast(Data.NewValue);	
}

void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::WoodChanged(const FOnAttributeChangeData& Data) const
{
	OnWoodChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::GoldChanged(const FOnAttributeChangeData& Data) const
{
	OnGoldChanged.Broadcast(Data.NewValue);
}
