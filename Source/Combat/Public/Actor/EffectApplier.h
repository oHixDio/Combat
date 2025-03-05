// Copyright Hiro

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EffectApplier.generated.h"

UCLASS()
class COMBAT_API AEffectApplier : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEffectApplier();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
