// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interaction/RTSActorInterface.h"
#include "RTSCharacterBase.h"
#include "AbilitySystem/RTSAttributeSet.h"
#include "RTSCharacter.generated.h"

USTRUCT(BlueprintType)
struct FMaterials
{
	GENERATED_BODY()
public:
	FMaterials()
	{
		Gold = 0;
		Wood = 0;
	}
	FMaterials(int32 NewGold , int32 NewWood)
	{
		Gold = NewGold;
		Wood = NewWood;
	}
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	int32 Gold;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	int32 Wood;

	FMaterials operator += (const FMaterials NewMaterials)
	{
		Gold += NewMaterials.Gold;
		Wood += NewMaterials.Wood;

		return *this;
	}
};

enum class ERTSActorType:uint8;

UCLASS()
class LINEOFDEFENSE_API ARTSCharacter : public ARTSCharacterBase ,public IRTSActorInterface 
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARTSCharacter();

	/** IRTSActorInterface */
	virtual void HightLightActor() override;
	virtual void UnHightLightActor() override;
	/** end IRTSActorInterface */
	
	UPROPERTY(BlueprintReadOnly)
	bool bHightlighted = false;

	UPROPERTY(BlueprintReadWrite,Category="RTS|Materials")
	int32 BackpackNum;

	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category="RTS|Materials")
	int32 BackpackCapacity;
    UFUNCTION(BlueprintCallable)
	void SaveMaterial (FMaterials Materials);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
    UFUNCTION(BlueprintImplementableEvent)
	void MaterialsIsGat();
	UPROPERTY(EditAnywhere,Category="RTS|Attributes")
	ERTSActorType Actortype;
	UFUNCTION(BlueprintCallable)
	void EmptuTheMaterial();
	UFUNCTION(BlueprintCallable)
	FMaterials GetBackpackSaveMaterials(){return BackpackSaveMaterials;}
	FMaterials BackpackSaveMaterials;
};
