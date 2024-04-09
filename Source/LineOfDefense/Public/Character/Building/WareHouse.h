// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActorComponent/BackpackInterface.h"
#include "Character/RTSAIBase.h"
#include "WareHouse.generated.h"

/**
 * 
*/

UCLASS()
class LINEOFDEFENSE_API AWareHouse : public ARTSAIBase ,public IBackpackInterface
{
	GENERATED_BODY()
public:
	AWareHouse();
	UFUNCTION(BlueprintCallable,Category="RTS|Backpack")
    virtual URTSMaterialsBackpack* GetRTSMaterialsBackpack() const override{return RTSMaterialsBackpack;}
protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<URTSMaterialsBackpack> RTSMaterialsBackpack;
};
