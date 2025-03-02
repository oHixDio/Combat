// Copyright Hiro

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "CombatAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class COMBAT_API UCombatAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	void GiveStartupAbilities(const TArray<TSubclassOf<UGameplayAbility>>& Abilities);

	void PressedAbilityAction(const FGameplayTag& InputTag);

	void TriggeredAbilityAction(const FGameplayTag& InputTag);

	void ReleasedAbilityAction(const FGameplayTag& InputTag);
};
