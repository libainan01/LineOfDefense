// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/RTSEffectActor.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/RTSAttributeSet.h"
#include "Components/SphereComponent.h"

// Sets default values
ARTSEffectActor::ARTSEffectActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UMeshComponent>("Mesh");
	SetRootComponent(Mesh);
	
	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetupAttachment(Mesh);

}

void ARTSEffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(IAbilitySystemInterface* ACSInterface = Cast<IAbilitySystemInterface>(OtherActor))
	{
		const URTSAttributeSet* URTSAttributes = Cast<URTSAttributeSet>(ACSInterface->GetAbilitySystemComponent()->GetAttributeSet(URTSAttributeSet::StaticClass()));
	}
}

void ARTSEffectActor::Endoverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
}

// Called when the game starts or when spawned
void ARTSEffectActor::BeginPlay()
{
	Super::BeginPlay();
	Sphere->OnComponentBeginOverlap.AddDynamic(this,&ARTSEffectActor::OnOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this,&ARTSEffectActor::Endoverlap);
}


