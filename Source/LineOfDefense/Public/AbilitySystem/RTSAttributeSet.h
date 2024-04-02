// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "RTSAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
    GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)
/**
 * 
 */



UCLASS()
class LINEOFDEFENSE_API URTSAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	URTSAttributeSet();
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	UPROPERTY(BlueprintReadOnly,Replicatedusing=OnRep_Health,Category="Vital Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(URTSAttributeSet,Health);
	
	UPROPERTY(BlueprintReadOnly,Replicatedusing=OnRep_MaxHealth,Category="Vital Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(URTSAttributeSet,MaxHealth);
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_Wood,Category="Vital Attributes|Materials")
	FGameplayAttributeData Wood;
	ATTRIBUTE_ACCESSORS(URTSAttributeSet,Wood);

	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_Gold,Category="Vital Attributes|Materials")
	FGameplayAttributeData Gold;
	ATTRIBUTE_ACCESSORS(URTSAttributeSet,Gold);
	
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const;

	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;

	UFUNCTION()
	void OnRep_Wood(const FGameplayAttributeData& OldWood) const;

	UFUNCTION()
	void OnRep_Gold(const FGameplayAttributeData& OldGold) const;

protected:
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
};
