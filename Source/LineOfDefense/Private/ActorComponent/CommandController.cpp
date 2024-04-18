// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponent/CommandController.h"

#include "Actor/ConstructionSide.h"
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

void UCommandController::SetCommandInfo(FCommandInfo CommandInfo,bool bPresets)
{
	//这是一条预设命令则直接加入命令队列
	if (bPresets)
	{
	    CommandQueue.Add(CommandInfo);
	}
	//这不是一条预设命令，则清空命令队列，在将当前命令加入到命令队列
	else
	{
		CommandQueue.Empty();
		bHasPresets = bPresets;
	}
		CommandQueue.Add(CommandInfo);
    //如果当前没有预设命令，则直接执行当前命令
	if (!bHasPresets&&!bPresets)
	{
	    ExecuteCommand();
	}
	//如过有预设明林，则在这里设置标签，防止下个预设命令直接执行
	bHasPresets = bPresets;
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

void UCommandController::NormalCommand()
{
	bool bActorStateIsSet = false;
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
						bActorStateIsSet = true;
						break;
					}
				default:;
				}
				break;
			}
		default:return;
		}
	}
	if(!bActorStateIsSet) Owner->SetActorState(ERTSActorStates::Moving);
	Owner->GetRTSAIController()->MonitorActorStates.Broadcast(CommandQueue[0]);
}

void UCommandController::ConstructionCommand()
{
	Owner->SetActorState(ERTSActorStates::Building);
	Owner->GetRTSAIController()->MonitorActorStates.Broadcast(CommandQueue[0]);
}

void UCommandController::ExecuteCommand()
{
    if(CommandQueue[0].bIsConstruction)
    {
	    ConstructionCommand();
    }
    else
    {
	    NormalCommand();
    }
}

