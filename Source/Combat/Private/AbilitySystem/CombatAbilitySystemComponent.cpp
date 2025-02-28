// Copyright Hiro


#include "AbilitySystem/CombatAbilitySystemComponent.h"

void UCombatAbilitySystemComponent::GiveAbilities(const TArray<TSubclassOf<UGameplayAbility>>& Abilities)
{
	for (const TSubclassOf<UGameplayAbility>& Ability : Abilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(Ability, 1); /* Levelを変えたいなら、引数をAbilityとLevelのMapにする。 */
		GiveAbilityAndActivateOnce(AbilitySpec);
	}
}
