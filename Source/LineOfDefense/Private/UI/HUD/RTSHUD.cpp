// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/RTSHUD.h"

#include "UI/WidgetController/OverlayWidgetController.h"
#include "UI/Widgets/RTSUserWidget.h"

UOverlayWidgetController* ARTSHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if(OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this,OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WCParams);
		OverlayWidgetController->BindCallbacksToDependencies();
		return OverlayWidgetController;
	}
	return OverlayWidgetController;
}

void ARTSHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
    checkf(OverlayWidgetClass,TEXT("Overlay Widget Class uninitialized,please fill out BP_RTSHUD"))
	checkf(OverlayWidgetControllerClass,TEXT("Overlay Widget Controller Class uninitialized,please fill out Bp_RTSHUD"))
	
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(),OverlayWidgetClass);
	OverlayWidget = Cast<URTSUserWidget>(Widget);

	const FWidgetControllerParams WidgetControllerParams(PC,PS,ASC,AS);
    UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);

	OverlayWidget->SetWidgetController(WidgetController);
	WidgetController->BroadcastInitialValues();
	Widget->AddToViewport();
}

void ARTSHUD::BeginPlay()
{
	Super::BeginPlay();

	UUserWidget* Widget = CreateWidget(GetWorld(),OverlayWidgetClass);
	Widget->AddToViewport();

}
