// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "RTSPlayerState.generated.h"

/**
 * 
 */

class URTSAbilitySystemComponent;
class URTSAttributeSet;

UCLASS()
class LINEOFDEFENSE_API ARTSPlayerState : public APlayerState , public IAbilitySystemInterface
{
	GENERATED_BODY()
public:
	ARTSPlayerState();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	URTSAttributeSet* GetAttributeSet() const {return RTSAttributes;}

protected:
	UPROPERTY()
	TObjectPtr<URTSAbilitySystemComponent> RTSAbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<URTSAttributeSet> RTSAttributes;
};
