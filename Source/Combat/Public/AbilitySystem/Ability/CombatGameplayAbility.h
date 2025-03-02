// Copyright Hiro

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "CombatGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class COMBAT_API UCombatGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UPROPERTY(Category = "Combat", EditDefaultsOnly)
	FGameplayTag StartupInputTag{};
};
