// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BackpackInterface.generated.h"

class URTSMaterialsBackpack;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UBackpackInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class LINEOFDEFENSE_API IBackpackInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual URTSMaterialsBackpack* GetRTSMaterialsBackpack() const=0; 
};
