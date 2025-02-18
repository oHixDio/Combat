// Copyright Hiro

#pragma once

#include "CoreMinimal.h"
#include "CombatCharacterBase.h"
#include "CombatPlayer.generated.h"

/**
 * 
 */
UCLASS()
class COMBAT_API ACombatPlayer : public ACombatCharacterBase
{
	GENERATED_BODY()

	// ====== ====== ======
	// Engine
	// ====== ====== ======
public:
	virtual void PossessedBy(AController* NewController) override;

	virtual void OnRep_PlayerState() override;

	// ====== ====== ======
	// Core
	// ====== ====== ======
private:
	/*
	 * ASC,ASをPlayerStateから受け取り、ASC->InitAbilityActorInfoを実行するハンドル関数.
	 */
	virtual void InitAbilityActorInfo() override;
	
};
