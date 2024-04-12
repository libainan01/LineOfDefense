// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interaction/RTSActorInterface.h"
#include "CommandController.generated.h"

class ARTSAIBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LINEOFDEFENSE_API UCommandController : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCommandController();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintCallable)
    void SetCommandInfo (FCommandInfo CommandInfo);
	UFUNCTION(BlueprintCallable)
	void FinishCommand(bool Successed);
protected:
	TArray<FCommandInfo> CommandQueue;
	UPROPERTY()
	TObjectPtr<ARTSAIBase> Owner;
	UPROPERTY()
	bool bIdInMission = false;
	void ExecuteCommand();
};
