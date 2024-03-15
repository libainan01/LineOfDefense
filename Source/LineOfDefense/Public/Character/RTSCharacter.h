// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interaction/RTSActorInterface.h"
#include "RTSCharacterBase.h"
#include "RTSCharacter.generated.h"

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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
