// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interaction/RTSActorInterface.h"
#include "Interaction/RTSMaterialActorInterface.h"
#include "RTSCharacterBase.h"
#include "AbilitySystem/RTSAttributeSet.h"
#include "RTSAIBase.generated.h"

UCLASS()
class LINEOFDEFENSE_API ARTSAIBase : public ARTSCharacterBase ,public IRTSActorInterface 
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARTSAIBase();

	/** IRTSActorInterface */
	virtual void HightLightActor() override;
	virtual void UnHightLightActor() override;
	
	UFUNCTION(BlueprintCallable)
	virtual void SetActorState(ERTSActorStates NewActorStates) override;
	UFUNCTION(BlueprintCallable)
	virtual ERTSActorStates GetActorStates() override{return ActorStates;};
	/** end IRTSActorInterface */
	
	UPROPERTY(BlueprintReadOnly)
	bool bHightlighted = false;

	UFUNCTION(BlueprintCallable)
	FRTSMaterials GetActorValue () const {return ActorValue;}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere,Category="RTS|Attributes")
	ERTSActorType Actortype;
	UPROPERTY(EditAnywhere,Category="RTS|Attributes")
	ERTSActorStates ActorStates;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	FRTSMaterials ActorValue;//这个单位值多少钱
};
