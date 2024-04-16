// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BuildingTool.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LINEOFDEFENSE_API UBuildingTool : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBuildingTool();
	UFUNCTION(BlueprintCallable)
	int32 GetConstructionEfficiency()const {return ConstructionEfficiency;}
	UFUNCTION(BlueprintCallable)
	int32 SetConstructionEfficiency(int32 NewConstructionEfficienxcy);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	UPROPERTY(BlueprintReadOnly,EditAnywhere)
	int32 ConstructionEfficiency = 1;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
