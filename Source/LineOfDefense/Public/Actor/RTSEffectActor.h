// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "Player/RTSPlayerState.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RTSEffectActor.generated.h"

class UGameplayEffect;
enum class ERTSActorType:uint8;

UCLASS()
class LINEOFDEFENSE_API ARTSEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARTSEffectActor();
    UPROPERTY(EditAnywhere)
	ERTSActorType ActorType;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
    UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor* TargetActor,TSubclassOf<UGameplayEffect> GameplayEffectClass);
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Applied Effects")
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Applied Effects")
	TSubclassOf<UGameplayEffect> DurationGameplayEffectClass;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Applied Effects")
	TSubclassOf<UGameplayEffect> InfiniteGameplayEffectClass;

};
