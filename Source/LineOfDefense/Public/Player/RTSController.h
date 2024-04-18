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
DECLARE_DYNAMIC_DELEGATE_OneParam(FUpdateSelectActorRequest,const TArray<TScriptInterface<IRTSActorInterface>>&,NewActors);

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
	UPROPERTY()
	FUpdateSelectActorRequest SelectActorRequest;
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	UPROPERTY()
	bool bIsPreset = false;

	/** ToolFunc **/
    FHitResult GetCursorHitResult (ECollisionChannel CollisionChannel);
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
    /** ConstructionEnd **/    


	
private:
	/** InputFunc **/
	void (ARTSController::*LeftButtonStarted)();
	void (ARTSController::*LeftButtonTriggered)();
	void (ARTSController::*LeftButtonEnd)();
	void (ARTSController::*RightButtonStarted)();
	void (ARTSController::*LeftShiftStarted)();
	void (ARTSController::*LeftShiftEnd)();
	/** InputFuncEnd **/

	/** InputActionAndContext **/
	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputMappingContext> RTSContext;
	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputAction> MouseLeftButtonAction;
	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputAction> MouseRightButtonAction;
	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputAction> LeftShiftClick;
	/** InputActionAndContextEnd **/
	
	FVector StartTracepoint;

	/** InputActionFunc **/
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
	void OnLeftShiftStarted(const FInputActionValue& InputActionValue);
	UFUNCTION()
	void OnLeftShiftEnd(const FInputActionValue& InputActionValue);
	/** InputActionFuncEnd **/

	/** InputActionCustomFunc **/
	UFUNCTION()
	void BeginDrawTraceBox();
	UFUNCTION()
	void DrawTraceBox();
	UFUNCTION()
	void FinishDrawTraceBox();
	UFUNCTION()
	void SetPresetCommand();
	UFUNCTION()
	void CancelPresetCommand();
	/** InputActionCustomFuncEnd **/
	
	TArray<TScriptInterface<IRTSActorInterface>> LastActors;
	TArray<TScriptInterface<IRTSActorInterface>> ThisActors;
	TArray<FHitResult> TraceBoxHitResults;
};
