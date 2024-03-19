// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "RTSPlayerState.generated.h"

/**
 * 
 */

class UAbilitySystemComponent;
class UAttributeSet;

UCLASS()
class LINEOFDEFENSE_API ARTSPlayerState : public APlayerState , public IAbilitySystemInterface
{
	GENERATED_BODY()
public:
	ARTSPlayerState();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const {return RTSAttributes;}

protected:
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> RTSAbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<UAttributeSet> RTSAttributes;
};
