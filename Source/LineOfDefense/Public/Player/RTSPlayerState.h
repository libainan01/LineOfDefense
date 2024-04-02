// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "RTSPlayerState.generated.h"

/**
 * 
 */
class UAbilitySystemComponent;
class UAttributeSet;

UENUM(BlueprintType)
enum class ERTSActorType:uint8
{
	Worker,
	WareHouse,
	Barracks,
	Material
};

UCLASS()
class LINEOFDEFENSE_API ARTSPlayerState : public APlayerState , public IAbilitySystemInterface
{
	GENERATED_BODY()
public:
	ARTSPlayerState();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const {return RTSAttributes;}
    UFUNCTION(BlueprintCallable)
	void SaveActor(AActor* TargetActor , ERTSActorType ActorType);
    UFUNCTION(BlueprintCallable)
	TArray<AActor*> GetActor(ERTSActorType ActorType);

protected:
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> RTSAbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<UAttributeSet> RTSAttributes;
    UPROPERTY()
	TArray<AActor*> WorkerArray;
	UPROPERTY()
	TArray<AActor*> WareHouseArray;
	UPROPERTY()
	TArray<AActor*> BarracksArray;
	UPROPERTY()
	TArray<AActor*> MaterialArray;
	
};
