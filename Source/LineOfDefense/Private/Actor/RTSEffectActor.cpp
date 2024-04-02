// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/RTSEffectActor.h"
#include "Player/RTSPlayerState.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ARTSEffectActor::ARTSEffectActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneRoot"));
}
// Called when the game starts or when spawned
void ARTSEffectActor::BeginPlay()
{
	Super::BeginPlay();
	ARTSPlayerState* PS = Cast<ARTSPlayerState>(UGameplayStatics::GetPlayerState(GetWorld(),0));
	PS->SaveActor(this,ActorType);
}

void ARTSEffectActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if(TargetASC == nullptr) return;
	
    check(GameplayEffectClass);
	//获得GameplayEffectContextHandle
	FGameplayEffectContextHandle EffectContextHandle = TargetASC->MakeEffectContext();
	//设置数据源
	EffectContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle EffectSpecHandle = TargetASC->MakeOutgoingSpec(GameplayEffectClass,1.f,EffectContextHandle);
	TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
}


