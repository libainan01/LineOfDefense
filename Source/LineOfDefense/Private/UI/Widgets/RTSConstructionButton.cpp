// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/RTSConstructionButton.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Player/RTSController.h"
#include "UI/WidgetController/RTSWidgetController.h"

void URTSConstructionButton::NativeConstruct()
{
	Super::NativeConstruct();
	ConstructionButton->OnReleased.AddDynamic(this,&URTSConstructionButton::RequestConstructionPermit);
}

void URTSConstructionButton::RequestConstructionPermit()
{
	Cast<ARTSController>(UGameplayStatics::GetPlayerController(GetWorld(),0))->ConstructionApplicationRequest.Execute(ConstructionInfo);
}
