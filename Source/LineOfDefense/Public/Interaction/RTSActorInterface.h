// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "RTSActorInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class URTSActorInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class LINEOFDEFENSE_API IRTSActorInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void HightLightActor() = 0 ;
	virtual void UnHightLightActor() = 0;
};
