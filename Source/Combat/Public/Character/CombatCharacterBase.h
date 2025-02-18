// Copyright Hiro

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CombatCharacterBase.generated.h"

UCLASS()
class COMBAT_API ACombatCharacterBase : public ACharacter
{
	GENERATED_BODY()

	// ====== ====== ======
	// Super
	// ====== ====== ======
public:
	ACombatCharacterBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
