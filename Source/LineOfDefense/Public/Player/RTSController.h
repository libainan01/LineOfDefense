// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RTSController.generated.h"

/**
 * 
 */
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;


UCLASS()
class LINEOFDEFENSE_API ARTSController : public APlayerController
{
	GENERATED_BODY()
public:
	ARTSController();
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
private:
	UPROPERTY(EditAnywhere,Category = "Input")
	TObjectPtr<UInputMappingContext> RTSContext;
	UPROPERTY(EditAnywhere,Category = "Input")
	TObjectPtr<UInputAction> MouseLeftButtonAction;

	FVector StartTracepoint;
	void BeginDrawTraceBox (const FInputActionValue& InputActionValue);
	void DrawTraceBox(const FInputActionValue& InputActionValue);
};
