// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RTSCharacterBase.h"
#include "GameFramework/Character.h"
#include "RTSObersver.generated.h"

UCLASS()
class LINEOFDEFENSE_API ARTSObersver : public ARTSCharacterBase
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARTSObersver();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	FVector CalculaterMoveDirection();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
