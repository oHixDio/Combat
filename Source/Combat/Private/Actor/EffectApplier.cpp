// Copyright Hiro


#include "Actor/EffectApplier.h"

// Sets default values
AEffectApplier::AEffectApplier()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEffectApplier::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEffectApplier::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

