// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interaction/RTSMaterialActorInterface.h"
#include "RTSActorInterface.generated.h"

class IRTSActorInterface;
class UCommandController;
class ARTSAIController;
class UBuildingTool;
class ARTSAIBase;
class AConstructionSide;

UENUM(BlueprintType)
enum class ERTSActorType:uint8
{
	Worker,
	WareHouse,
	Barracks,
	Material,
	ConstructionSite
};

USTRUCT(BlueprintType)
struct FConstructionInfo
{
	GENERATED_BODY()
	FConstructionInfo()
	{
		ConstructionTime = 0;
		BlueprintClass = nullptr;
	}
	FConstructionInfo(int32 NewConstructionTime,FRTSMaterials NewMaterials,TSubclassOf<ARTSAIBase> NewBlueprintClass)
	{
		ConstructionTime = NewConstructionTime;
		ActorValue = NewMaterials;
		BlueprintClass = NewBlueprintClass;
	}
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	int32 ConstructionTime;
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	FRTSMaterials ActorValue;
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TSubclassOf<ARTSAIBase> BlueprintClass;
};

UENUM(BlueprintType)
enum class ERTSActorStates:uint8
{
	Idle,
	Moving,
	Gathering,
	Building
};

USTRUCT(BlueprintType)
struct FCommandInfo
{
	GENERATED_BODY()
	FCommandInfo()
	{
		Target = nullptr;
		Location = FVector::ZeroVector;
		bIsConstruction = false;
		ConstructionSide = nullptr;
	}
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TScriptInterface<IRTSActorInterface> Target;
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	FVector Location;
    UPROPERTY()
	bool bIsConstruction;
	void SetConstructionSide(AConstructionSide* NewConstructionSide)
	{
		ConstructionSide = NewConstructionSide;
		bIsConstruction = true;
	};

	AConstructionSide* GetConstructionSide() const {return ConstructionSide;}
protected:
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	AConstructionSide* ConstructionSide;
};
// This class does not need to be modified.
UINTERFACE(MinimalAPI,Blueprintable)
class URTSActorInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
//
class LINEOFDEFENSE_API IRTSActorInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void HightLightActor() = 0 ;
	virtual void UnHightLightActor() = 0;
	virtual void SetActorState(ERTSActorStates NewActorStates);
	virtual ERTSActorStates GetActorStates();
	virtual ERTSActorType GetActorType() const;
	virtual UCommandController* GetCommandController()const;
	virtual ARTSAIController* GetRTSAIController() const;
	virtual UBuildingTool* GetBuildingTool() const;
	
};
