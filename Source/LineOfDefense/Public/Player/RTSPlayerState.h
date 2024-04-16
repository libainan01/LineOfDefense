// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "ActorComponent/BackpackInterface.h"
#include "Interaction/RTSActorInterface.h"
#include "Interaction/RTSMaterialActorInterface.h"
#include "RTSPlayerState.generated.h"

/**
 * 
 */
class UAbilitySystemComponent;
class UAttributeSet;
class URTSMaterialsBackpack;

USTRUCT(BlueprintType)
struct FRTSActorInfo
{
	GENERATED_BODY()
    FRTSActorInfo()
	{
		RTSActorLocation = FVector::ZeroVector;
		RTSActorInterface = nullptr;
	}
	FRTSActorInfo(FVector NewLocation , TScriptInterface<IRTSActorInterface> NewActor):RTSActorLocation(NewLocation),RTSActorInterface(NewActor){}
	
	UPROPERTY(BlueprintReadOnly,EditAnywhere)
	FVector RTSActorLocation;
	UPROPERTY(BlueprintReadOnly,EditAnywhere)
	TScriptInterface<IRTSActorInterface> RTSActorInterface;
};

UCLASS()
class LINEOFDEFENSE_API ARTSPlayerState : public APlayerState , public IAbilitySystemInterface , public IBackpackInterface
{
	GENERATED_BODY()
public:
	ARTSPlayerState();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const {return RTSAttributes;}
	UFUNCTION(BlueprintCallable)
    void SaveActor(FRTSActorInfo TargetActor , ERTSActorType ActorType);
	UFUNCTION(BlueprintCallable)
	TArray<FRTSActorInfo> GetActor(ERTSActorType ActorType);
	//UFUNCTION(BlueprintCallable)
	//void DeleteActor(FRTSActorInfo TargetActor, ERTSActorType ActorType);
	UFUNCTION(BlueprintCallable,Category="RTS|Backpack")
	virtual URTSMaterialsBackpack* GetRTSMaterialsBackpack() const override{return Backpack;}

protected:

	UFUNCTION(BlueprintCallable)
	void UpdateRTSMaterialInAttributes()const;
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> RTSAbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<UAttributeSet> RTSAttributes;
    UPROPERTY(BlueprintReadOnly)
	TArray<FRTSActorInfo> WorkerArray;
	UPROPERTY(BlueprintReadOnly)
	TArray<FRTSActorInfo> WareHouseArray;
	UPROPERTY(BlueprintReadOnly)
	TArray<FRTSActorInfo> BarracksArray;
	UPROPERTY(BlueprintReadOnly)
	TArray<FRTSActorInfo> MaterialArray;
	UPROPERTY(EditAnywhere)
	TObjectPtr<URTSMaterialsBackpack> Backpack;
};
