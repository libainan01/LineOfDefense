// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/RTSEffectActor.h"
#include "ConstructionSide.generated.h"
/**
 * 
 */
class ARTSPlayerState;

UCLASS()
class LINEOFDEFENSE_API AConstructionSide : public ARTSEffectActor
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	float Building(int32 ConstructionEfficiency);
	UFUNCTION(BlueprintCallable)
	void SetConstructionInfo(FConstructionInfo NewConstructionInfo);
	UFUNCTION(BlueprintCallable)
	void InitialConstructionSide (FConstructionInfo NewConstructioninfo , ARTSPlayerState* PS);
protected:
	int32 ConstructionProgress;
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	FConstructionInfo ConstructionInfo;
	UFUNCTION()
	virtual void BeginPlay() override;
	UFUNCTION()
	void ConsumableMaterials (FRTSMaterials ConsumableMaterials) const;
	UPROPERTY()
	TObjectPtr<ARTSPlayerState> PlayerState;
	UFUNCTION()
	void FinishBuilding();
};
