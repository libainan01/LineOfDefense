// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interaction/RTSActorInterface.h"
#include "RTSCharacterBase.h"
#include "AbilitySystem/RTSAttributeSet.h"
#include "RTSCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWoodChanged,float,NewWood);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGoldChanged,float,NewGold);

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

	UPROPERTY(BlueprintAssignable , Category="GAS|Attributs")
	FOnWoodChanged OnWoodChange;

	UPROPERTY(BlueprintAssignable , Category="GAS|Attributs")
	FOnGoldChanged OnGoldChange;

	UPROPERTY(BlueprintReadOnly,Category="GAS|Attributs")
	int32 BackpackCapacity;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void BindCallbacksToDependencies();
	
	void WoodChange (const FOnAttributeChangeData& Data) const;
	void GoldChange (const FOnAttributeChangeData& Data) const;
};
