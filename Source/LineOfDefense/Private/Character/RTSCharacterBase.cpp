// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/RTSCharacterBase.h"
#include "AbilitySystem/RTSAbilitySystemComponent.h"
#include "AbilitySystem/RTSAttributeSet.h"

// Sets default values
ARTSCharacterBase::ARTSCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	RTSAbilitySystemComponent = CreateDefaultSubobject<URTSAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	RTSAbilitySystemComponent->SetIsReplicated(true);
	RTSAbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	
	RTSAttributes = CreateDefaultSubobject<URTSAttributeSet>(TEXT("Attributes"));


}

UAbilitySystemComponent* ARTSCharacterBase::GetAbilitySystemComponent() const
{
	return RTSAbilitySystemComponent;
}

// Called when the game starts or when spawned
void ARTSCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARTSCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARTSCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

