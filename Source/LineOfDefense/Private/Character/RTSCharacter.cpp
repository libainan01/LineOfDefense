// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/RTSCharacter.h"

#include "AbilitySystem/RTSAttributeSet.h"
#include "Kismet/GameplayStatics.h"
#include "Player/RTSPlayerState.h"

// Sets default values
ARTSCharacter::ARTSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ARTSCharacter::HightLightActor()
{
	bHightlighted = true;
}

void ARTSCharacter::UnHightLightActor()
{
	bHightlighted = false;
}

void ARTSCharacter::SaveMaterial(FMaterials Materials)
{
	BackpackNum += Materials.Gold;
	BackpackNum += Materials.Wood;

	BackpackSaveMaterials += Materials;
}

// Called when the game starts or when spawned
void ARTSCharacter::BeginPlay()
{
	Super::BeginPlay();
	RTSAbilitySystemComponent->InitAbilityActorInfo(this,this);
    Cast<ARTSPlayerState>(UGameplayStatics::GetPlayerState(GetWorld(),0))->SaveActor(this,Actortype);
}

void ARTSCharacter::EmptuTheMaterial()
{
	BackpackSaveMaterials.Gold = 0;
	BackpackSaveMaterials.Wood = 0;
	BackpackNum = 0;
}


