// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/PlayerController.h"
#include "RTSController.generated.h"

/**
 * 
 */
class UInputMappingContext;
class UInputAction;
class IRTSActorInterface;
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
	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputMappingContext> RTSContext;
	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputAction> MouseLeftButtonAction;
	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputAction> MouseRightButtonAction;

	FVector StartTracepoint;
	UFUNCTION()
	void BeginDrawTraceBox (const FInputActionValue& InputActionValue);
	UFUNCTION()
	void DrawTraceBox(const FInputActionValue& InputActionValue);
	UFUNCTION()
	void FinishDrawTraceBox(const FInputActionValue& InputActionValue);
	UFUNCTION()
	void RightButtonClick(const FInputActionValue& InputActionValue);
	TArray<TScriptInterface<IRTSActorInterface>> LastActors;
	TArray<TScriptInterface<IRTSActorInterface>> ThisActors;
	TArray<FHitResult> TraceBoxHitResults;
};
