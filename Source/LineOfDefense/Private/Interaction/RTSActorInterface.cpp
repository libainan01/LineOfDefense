// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/RTSActorInterface.h"

// Add default functionality here for any IRTSActorInterface functions that are not pure virtual.
void IRTSActorInterface::SetActorState(ERTSActorStates NewActorStates)
{
}

ERTSActorStates IRTSActorInterface::GetActorStates()
{
	return ERTSActorStates::Idle;
}
