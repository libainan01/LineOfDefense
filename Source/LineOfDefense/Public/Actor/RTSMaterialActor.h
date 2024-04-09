// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/RTSEffectActor.h"
#include "Interaction/RTSMaterialActorInterface.h"
#include "RTSMaterialActor.generated.h"

/**
 * 
 */
UCLASS()
class LINEOFDEFENSE_API ARTSMaterialActor : public ARTSEffectActor , public IRTSMaterialActorInterface
{
	GENERATED_BODY()
public:
	/** IRTSMaterialActorInterface **/
	virtual FRTSMaterials BeGathering(int32 GatherEfficiency) override;
	/** EndIRTSMaterialActorInterface **/
protected:
	UFUNCTION()
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere,DisplayName="RTSMaterialTotal")
	FRTSMaterials RTSMaterialsTotal;
};
