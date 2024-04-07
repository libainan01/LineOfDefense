// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interaction/RTSMaterialActorInterface.h"
#include "RTSMaterialsBackpack.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LINEOFDEFENSE_API URTSMaterialsBackpack : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URTSMaterialsBackpack();
    UFUNCTION(BlueprintCallable)
	FRTSMaterials StoreRTSMaterials(FRTSMaterials NewMaterials);
	UFUNCTION(BlueprintCallable)
	FRTSMaterials ConsumableRTSMaterials(FRTSMaterials NewMaterials);
	UFUNCTION(BlueprintCallable)
	FRTSMaterials GetRTSMaterials(){return StoringRTSMaterials;}

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere,Category="RTS|Attributes")
	int32 BackpackCapacity;//背包容量
	UPROPERTY(BlueprintReadOnly)
	FRTSMaterials StoringRTSMaterials; 

public:	

};
