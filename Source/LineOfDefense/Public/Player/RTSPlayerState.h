// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "Interaction/RTSActorInterface.h"
#include "RTSPlayerState.generated.h"

/**
 * 
 */
class UAbilitySystemComponent;
class UAttributeSet;

UCLASS()
class LINEOFDEFENSE_API ARTSPlayerState : public APlayerState , public IAbilitySystemInterface
{
	GENERATED_BODY()
public:
	ARTSPlayerState();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const {return RTSAttributes;}
	UFUNCTION(BlueprintCallable)
    void SaveActor(TScriptInterface<IRTSActorInterface> TargetActor , ERTSActorType ActorType);
	UFUNCTION(BlueprintCallable)
	TArray<TScriptInterface<IRTSActorInterface>> GetActor(ERTSActorType ActorType);

protected:
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> RTSAbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<UAttributeSet> RTSAttributes;
    UPROPERTY(BlueprintReadOnly)
	TArray<TScriptInterface<IRTSActorInterface>> WorkerArray;
	UPROPERTY(BlueprintReadOnly)
	TArray<TScriptInterface<IRTSActorInterface>> WareHouseArray;
	UPROPERTY(BlueprintReadOnly)
	TArray<TScriptInterface<IRTSActorInterface>> BarracksArray;
	UPROPERTY(BlueprintReadOnly)
	TArray<TScriptInterface<IRTSActorInterface>> MaterialArray;
	
};
