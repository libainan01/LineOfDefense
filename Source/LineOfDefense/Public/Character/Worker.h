// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActorComponent/BackpackInterface.h"
#include "Character/RTSAIBase.h"
#include "Worker.generated.h"

/**
 * 
 */

UCLASS()
class LINEOFDEFENSE_API AWorker : public ARTSAIBase ,public IBackpackInterface
{
	GENERATED_BODY()
public:
	AWorker();
	UFUNCTION(BlueprintCallable)
	FRTSMaterials GatherRTSMaterials(TScriptInterface<IRTSMaterialActorInterface> RTSMaterialActor);
	UFUNCTION(BlueprintCallable,Category="RTS|Backpack")
    virtual URTSMaterialsBackpack* GetRTSMaterialsBackpack() const override{return RTSMaterialsBackpack;}
protected:
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="RTS|Attributes")
	int32 GatheringEfficiency = 1;
    UPROPERTY(EditAnywhere)
	TObjectPtr<URTSMaterialsBackpack> RTSMaterialsBackpack;
	
	
};
