// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Worker.h"

#include "ActorComponent/RTSMaterialsBackpack.h"

AWorker::AWorker()
{
	RTSMaterialsBackpack = CreateDefaultSubobject<URTSMaterialsBackpack>(TEXT("Backpack"));
}

FRTSMaterials AWorker::GatherRTSMaterials(TScriptInterface<IRTSMaterialActorInterface> RTSMaterialActor)
{
	int32 PerGatheringEfficiency = GatheringEfficiency;
	//检测这次添加材料会不会超出背包容量
	if (RTSMaterialsBackpack->GetBackpackCapacity()<=RTSMaterialsBackpack->GetStoringRTSMaterials().GetTotal() + GatheringEfficiency)
	{
		PerGatheringEfficiency = RTSMaterialsBackpack->GetBackpackCapacity() - RTSMaterialsBackpack->GetStoringRTSMaterials().GetTotal();
	}
	
	//从MaterialsActor处采集素材，并存储到背包里
	RTSMaterialsBackpack->StoreRTSMaterials(RTSMaterialActor->BeGathering(PerGatheringEfficiency));
	return RTSMaterialsBackpack->GetRTSMaterials();
}

