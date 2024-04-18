// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/RTSUserWidget.h"

#include "UI/WidgetController/OverlayWidgetController.h"

void URTSUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}
