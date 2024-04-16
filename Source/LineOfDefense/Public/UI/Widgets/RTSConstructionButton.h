// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interaction/RTSActorInterface.h"
#include "UI/Widgets/RTSUserWidget.h"
#include "RTSConstructionButton.generated.h"
class UButton;
class AConstructionSide;
/**
 * 
 */
UCLASS()
class LINEOFDEFENSE_API URTSConstructionButton : public URTSUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;
	UPROPERTY(meta=(BindWidget))
	UButton* ConstructionButton;
    UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Building")
	FConstructionInfo ConstructionInfo;

	UFUNCTION()
	void RequestConstructionPermit();
	
};
