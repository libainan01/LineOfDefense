// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponent/CommandController.h"

#include "Character/RTSAIBase.h"
#include "Player/AI/RTSAIController.h"

// Sets default values for this component's properties
UCommandController::UCommandController()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}


// Called when the game starts
void UCommandController::BeginPlay()
{
	Super::BeginPlay();
    Owner = Cast<ARTSAIBase>(GetOwner());
    
	// ...
	
}


// Called every frame
void UCommandController::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCommandController::SetCommandInfo(FCommandInfo CommandInfo)
{
	CommandQueue.Add(CommandInfo);
	ExecuteCommand();
}

void UCommandController::FinishCommand(bool Successed)
{
	if (Successed)
	{
		CommandQueue.RemoveAt(0);
	}
	if (!CommandQueue.IsEmpty())
	{
		ExecuteCommand();
	}
}

void UCommandController::ExecuteCommand()
{
	if (bIdInMission)
	{
		return;
	}
	bIdInMission = true;
	if (CommandQueue[0].Target !=nullptr)
	{
		const ERTSActorType ActorType = CommandQueue[0].Target->GetActorType();

		 switch (Cast<IRTSActorInterface>(GetOwner())->GetActorType())
		 {
		 case ERTSActorType::Worker:
		 	{
			    switch (ActorType)
			    {
			    case ERTSActorType::Material:
				    {
					    Owner->SetActorState(ERTSActorStates::Gathering);
			    		break;
				    }
			    	default:;
			    }
		 	}
		 	default:;
		 }
	}
	Owner->GetRTSAIController()->MonitorActorStates.Broadcast(Owner->GetActorStates());
}

