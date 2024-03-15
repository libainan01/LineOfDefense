// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interaction/RTSActorInterface.h"
#include "AbilitySystemInterface.h"
#include "RTSCharacter.generated.h"

class URTSAbilitySystemComponent;
class URTSAttributeSet;

UCLASS()
class LINEOFDEFENSE_API ARTSCharacter : public ACharacter ,public IRTSActorInterface ,public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARTSCharacter();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	URTSAttributeSet* GetAttributeSet() const{return RTSAttributes;}

	virtual void HightLightActor() override;
	virtual void UnHightLightActor() override;
	
	UPROPERTY(BlueprintReadOnly)
	bool bHightlighted = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	TObjectPtr<URTSAbilitySystemComponent> RTSAbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<URTSAttributeSet> RTSAttributes;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
