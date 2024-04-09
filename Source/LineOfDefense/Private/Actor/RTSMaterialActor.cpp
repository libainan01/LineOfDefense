// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/RTSMaterialActor.h"

FRTSMaterials ARTSMaterialActor::BeGathering(int32 GatherEfficiency)
{
	FRTSMaterials PreGatherRTSMaterial(GatherEfficiency);//申请采集的量
	FRTSMaterials LastRTSMaterialSTotal = RTSMaterialsTotal;
	RTSMaterialsTotal.ConsumableMaterials(PreGatherRTSMaterial);//消耗材料
	PreGatherRTSMaterial = LastRTSMaterialSTotal - RTSMaterialsTotal;
	if (RTSMaterialsTotal.GetTotal()<=0)
	{
		FRTSMaterials GatherRTSMaterial = RTSMaterialsTotal.AddMaterials(PreGatherRTSMaterial);
		this->Destroy();
		return GatherRTSMaterial;
	}

	return PreGatherRTSMaterial;
}

void ARTSMaterialActor::BeginPlay()
{
	Super::BeginPlay();
	FRTSMaterials FrtsMaterials(RTSMaterialsTotal.GetGold(),RTSMaterialsTotal.GetWood());
	RTSMaterialsTotal = FrtsMaterials;
}
