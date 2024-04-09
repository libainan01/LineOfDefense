// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Building/WareHouse.h"

#include "ActorComponent/RTSMaterialsBackpack.h"

AWareHouse::AWareHouse()
{
	RTSMaterialsBackpack = CreateDefaultSubobject<URTSMaterialsBackpack>(TEXT("Backpack"));
}
