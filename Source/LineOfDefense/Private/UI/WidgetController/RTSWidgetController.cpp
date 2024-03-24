// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/RTSWidgetController.h"

void URTSWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WCParams)
{
	PlayerController = WCParams.PlayerController;
	PlayerState = WCParams.PlayerState;
	AbilitySystemComponent = WCParams.AbilitySystemComponent;
	AttributeSet = WCParams.Attributes;
}

void URTSWidgetController::BroadcastInitialValues()
{
	
}

void URTSWidgetController::BindCallbacksToDependencies()
{
}
