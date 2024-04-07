// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "RTSMaterialActorInterface.generated.h"

USTRUCT(BlueprintType)
struct FRTSMaterials
{
	GENERATED_BODY()
	
	FRTSMaterials()
	{
		Gold = 0;
		Wood = 0;
		Total = Wood + Gold;
	}
	FRTSMaterials(int32 NewGold , int32 NewWood)
	{
		Gold = NewGold;
		Wood = NewWood;
		Total = NewGold + NewWood;
	}

	FRTSMaterials AddMaterials(const FRTSMaterials NewMaterials)
	{
		return *this += NewMaterials;
	}

	FRTSMaterials ConsumableMaterials(const FRTSMaterials NewMaterials)
	{
		return *this -= NewMaterials;
	}
	
	int32 GetGold() const {return Gold;}
	
	int32 GetWood() const {return Wood;}
	
	int32 GetTotal() const {return Total;}
protected:
	
	UPROPERTY(BlueprintReadOnly)
	int32 Total;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	int32 Gold;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	int32 Wood;

private:
	FRTSMaterials operator += (const FRTSMaterials NewMaterials)
	{
		Gold += NewMaterials.Gold;
		Wood += NewMaterials.Wood;
		Total += Total;

		return *this;
	}
	FRTSMaterials operator -= (const FRTSMaterials NewMaterials)
	{
		Gold -= NewMaterials.Gold;
		Wood -= NewMaterials.Wood;
		Total -= NewMaterials.Total;

		return *this;
	}
};
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class URTSMaterialActorInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class LINEOFDEFENSE_API IRTSMaterialActorInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
};
