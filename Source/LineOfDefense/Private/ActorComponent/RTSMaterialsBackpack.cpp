// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponent/RTSMaterialsBackpack.h"

// Sets default values for this component's properties
URTSMaterialsBackpack::URTSMaterialsBackpack()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

FRTSMaterials URTSMaterialsBackpack::StoreRTSMaterials(FRTSMaterials NewMaterials)
{
	StoringRTSMaterials.AddMaterials(NewMaterials);
	if (BackpackFalling.IsBound())
	{
		BackpackFalling.Broadcast(StoringRTSMaterials.GetTotal()>=BackpackCapacity);
	}
	OnRTSMaterialsChanging.Broadcast(StoringRTSMaterials);
	return StoringRTSMaterials;
}

FRTSMaterials URTSMaterialsBackpack::ConsumableRTSMaterials(FRTSMaterials NewMaterials)
{
	StoringRTSMaterials.ConsumableMaterials(NewMaterials);
	if (BackpackFalling.IsBound())
	{
		BackpackFalling.Broadcast(StoringRTSMaterials.GetTotal()>=BackpackCapacity);
	}
	OnRTSMaterialsChanging.Broadcast(StoringRTSMaterials);
	return StoringRTSMaterials;
}


int32 URTSMaterialsBackpack::SetBackpackCapacity(int32 NewBackpackCapacity)
{
	BackpackCapacity = NewBackpackCapacity;
	return NewBackpackCapacity;
}

void URTSMaterialsBackpack::SubRTSMaterialsToTarget(URTSMaterialsBackpack* NewRTSBackpack)
{
	NewRTSBackpack->StoreRTSMaterials(StoringRTSMaterials);
	StoringRTSMaterials = FRTSMaterials(0);
}

// Called when the game starts
void URTSMaterialsBackpack::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


