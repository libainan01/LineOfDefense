// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "RTSCharacterBase.generated.h"

class URTSAbilitySystemComponent;
class URTSAttributeSet;
UCLASS()
class LINEOFDEFENSE_API ARTSCharacterBase : public ACharacter ,public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARTSCharacterBase();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	URTSAttributeSet* GetAttributeSet() const{return RTSAttributes;}

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
