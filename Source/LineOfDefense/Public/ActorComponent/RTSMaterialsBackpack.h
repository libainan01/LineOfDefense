// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interaction/RTSMaterialActorInterface.h"
#include "RTSMaterialsBackpack.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBackpackFallingSignature,bool,BackpackIsFalling);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRTSMaterialsChangeSignature,FRTSMaterials,NewRTSMaterials);

class ARTSPlayerState;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LINEOFDEFENSE_API URTSMaterialsBackpack : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URTSMaterialsBackpack();
    UFUNCTION(BlueprintCallable,Category="RTS|Backpack")
	FRTSMaterials StoreRTSMaterials(FRTSMaterials NewMaterials);
	UFUNCTION(BlueprintCallable,Category="RTS|Backpack")
	FRTSMaterials ConsumableRTSMaterials(FRTSMaterials NewMaterials);
	UFUNCTION(BlueprintCallable,Category="RTS|Backpack")
	FRTSMaterials GetRTSMaterials(){return StoringRTSMaterials;}
	UFUNCTION(BlueprintCallable,Category="RTS|Backpack")
	int32 GetBackpackCapacity() const {return BackpackCapacity;}
	UFUNCTION(BlueprintCallable,Category="RTS|Backpack")
	int32 SetBackpackCapacity(int32 NewBackpackCapacity);
	UFUNCTION(BlueprintCallable,Category="RTS|Backpack")
	FRTSMaterials GetStoringRTSMaterials() const {return StoringRTSMaterials;}
	UFUNCTION(BlueprintCallable,Category="RTS|Backpack")
	void SubRTSMaterialsToTarget(URTSMaterialsBackpack* NewRTSBackpack);
	
    UPROPERTY(BlueprintAssignable,Category="RTS|Backpack")
	FBackpackFallingSignature BackpackFalling;
	UPROPERTY(BlueprintAssignable,Category="RTS|Backpack")
	FRTSMaterialsChangeSignature OnRTSMaterialsChanging;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere,Category="RTS|Attributes")
	int32 BackpackCapacity;//背包容量
	UPROPERTY(BlueprintReadOnly)
	FRTSMaterials StoringRTSMaterials; 

public:	

};
