// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/RTSAttributeSet.h"
#include "Interaction/RTSActorInterface.h"
#include "UI/WidgetController/RTSWidgetController.h"
#include "OverlayWidgetController.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float ,NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChangedSignature, float ,NewMaxHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWoodChangedSignature,float,NewWood);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGoldChangedSignature,float,NewGold);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSelectActorChangedSignature,const TArray<TScriptInterface<IRTSActorInterface>>&,NewActors);

UCLASS(BlueprintType , Blueprintable)
class LINEOFDEFENSE_API UOverlayWidgetController : public URTSWidgetController
{
	GENERATED_BODY()
public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;
	UFUNCTION(BlueprintImplementableEvent)
	void RTSMaterialsUptate(const FRTSMaterials& NewMaterials);

	UPROPERTY(BlueprintAssignable,Category="GAS|Attributes")
	FOnHealthChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable,Category="GAS|Attributes")
	FOnMaxHealthChangedSignature OnMaxHealthChanged;

	UPROPERTY(BlueprintAssignable,Category="GAS|Attributes")
	FOnWoodChangedSignature OnWoodChanged;

	UPROPERTY(BlueprintAssignable,Category="GAS|Attributes")
	FOnGoldChangedSignature OnGoldChanged;

	UPROPERTY(BlueprintAssignable,Category="RTS|Broadcast")
	FOnSelectActorChangedSignature OnSelectActorChanged;
protected:
	void HealthChanged(const FOnAttributeChangeData& Data) const;
	void MaxHealthChanged(const FOnAttributeChangeData& Data) const;
	void WoodChanged(const FOnAttributeChangeData& Data) const;
	void GoldChanged(const FOnAttributeChangeData& Data) const;
    UFUNCTION()
	void SelectActorChanged(const TArray<TScriptInterface<IRTSActorInterface>>& NewActors);
	UFUNCTION()
	void OnRTSMaterialsChanged(FRTSMaterials NewFRTSMaterials);
	virtual void WidgetControllerHasInitial() override;
};
