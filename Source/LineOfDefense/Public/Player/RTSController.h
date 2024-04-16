// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interaction/RTSActorInterface.h"
#include "InputActionValue.h"
#include "GameFramework/PlayerController.h"
#include "RTSController.generated.h"

/**
 * 
 */
class UInputMappingContext;
class UInputAction;
class AConstructionSide;
struct FInputActionValue;

DECLARE_DYNAMIC_DELEGATE_OneParam(FConstructionApplicationRequest,FConstructionInfo,ConstructionInfo);
DECLARE_DYNAMIC_DELEGATE_OneParam(FConstructionApplicationSignature,bool,bAllow);

UCLASS()
class LINEOFDEFENSE_API ARTSController : public APlayerController
{
	GENERATED_BODY()
public:
	ARTSController();
	UFUNCTION()
	void MakeCommandInfo(FCommandInfo NewCommandInfo);
	UPROPERTY()
	FConstructionApplicationRequest ConstructionApplicationRequest;
	UPROPERTY()
	FConstructionApplicationSignature ConstructionApplicationSignature;
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	UPROPERTY()
	bool bIsPreset = false;

	/** ToolFunc **/
    FHitResult GetCursorHitResult ();
   ///** ToolFuncEnd**/

    /** Construction**/
    UFUNCTION()
    void ReviewConstructionApplication(FConstructionInfo NewCosntructionInfo);
    UFUNCTION()
    void CheckConstruction();
    UFUNCTION()
    void ApproveConstructionApplication();
    UPROPERTY()
    FTimerHandle ConstructionReviewTimerHandle;
    UPROPERTY()
    TObjectPtr<AConstructionSide> ConstructionSide;
    UPROPERTY(EditAnywhere,Category="Building")
    TSubclassOf<AConstructionSide> ConstructionSideClass;
    /** ConstructionEnd **    
    /** InputFunc **/
    void (ARTSController::*LeftButtonStarted)();
    void (ARTSController::*LeftButtonTriggered)();
    void (ARTSController::*LeftButtonEnd)();
    void (ARTSController::*RightButtonStarted)();
    /** InputFuncEnd **/

	
private:
	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputMappingContext> RTSContext;
	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputAction> MouseLeftButtonAction;
	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputAction> MouseRightButtonAction;

	FVector StartTracepoint;
	UFUNCTION()
	void OnLeftButtonStarted (const FInputActionValue& InputActionValue);
	UFUNCTION()
	void OnLeftButtonTriggered(const FInputActionValue& InputActionValue);
	UFUNCTION()
	void OnLeftButtonEnd(const FInputActionValue& InputActionValue);
	UFUNCTION()
	void RightButtonClick(const FInputActionValue& InputActionValue);
	UFUNCTION()
	void RightButtonRelease(const FInputActionValue& InputActionValue);

	UFUNCTION()
	void BeginDrawTraceBox();
	UFUNCTION()
	void DrawTraceBox();
	UFUNCTION()
	void FinishDrawTraceBox();
	
	TArray<TScriptInterface<IRTSActorInterface>> LastActors;
	TArray<TScriptInterface<IRTSActorInterface>> ThisActors;
	TArray<FHitResult> TraceBoxHitResults;
};
