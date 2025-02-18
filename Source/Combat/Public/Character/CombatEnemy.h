// Copyright Hiro

#pragma once

#include "CoreMinimal.h"
#include "CombatCharacterBase.h"
#include "CombatEnemy.generated.h"

/**
 * 
 */
UCLASS()
class COMBAT_API ACombatEnemy : public ACombatCharacterBase
{
	GENERATED_BODY()

	// ====== ====== ======
	// Engine
	// ====== ====== ======
public:
	ACombatEnemy();
protected:
	virtual void BeginPlay() override;

	// ====== ====== ======
	// Core
	// ====== ====== ======
private:
	virtual void InitAbilityActorInfo() override;
};
