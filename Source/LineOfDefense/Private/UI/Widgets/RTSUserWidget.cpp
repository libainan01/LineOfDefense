// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/RTSUserWidget.h"

void URTSUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}
