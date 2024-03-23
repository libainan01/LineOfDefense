// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/RTSHUD.h"

#include "UI/Widgets/RTSUserWidget.h"

void ARTSHUD::BeginPlay()
{
	Super::BeginPlay();

	UUserWidget* Widget = CreateWidget(GetWorld(),OverlayWidgetclass);
	Widget->AddToViewport();

}
