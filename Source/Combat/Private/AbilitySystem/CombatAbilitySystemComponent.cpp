// Copyright Hiro


#include "AbilitySystem/CombatAbilitySystemComponent.h"

#include "AbilitySystem/Ability/CombatGameplayAbility.h"

void UCombatAbilitySystemComponent::GiveStartupAbilities(const TArray<TSubclassOf<UGameplayAbility>>& Abilities)
{
	for (const TSubclassOf<UGameplayAbility>& Ability : Abilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(Ability, 1);
		if (const UCombatGameplayAbility* CombatAbility = Cast<UCombatGameplayAbility>(AbilitySpec.Ability))
		{
			AbilitySpec.GetDynamicSpecSourceTags().AddTag(CombatAbility->StartupInputTag);
			GiveAbility(AbilitySpec);
		}
	}
}

void UCombatAbilitySystemComponent::PressedAbilityAction(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid())
	{
		return;
	}

	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.GetDynamicSpecSourceTags().HasTagExact(InputTag))
		{
			if (!AbilitySpec.IsActive() && !AbilitySpec.InputPressed)
			{
				AbilitySpecInputPressed(AbilitySpec);
				TryActivateAbility(AbilitySpec.Handle);
			}
		}
	}
}

void UCombatAbilitySystemComponent::TriggeredAbilityAction(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid())
	{
		return;
	}

	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.GetDynamicSpecSourceTags().HasTagExact(InputTag))
		{
			if (!AbilitySpec.InputPressed)
			{
				AbilitySpecInputPressed(AbilitySpec);
			}
			if (!AbilitySpec.IsActive())
			{
				TryActivateAbility(AbilitySpec.Handle);
			}
		}
	}
}

void UCombatAbilitySystemComponent::ReleasedAbilityAction(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid())
	{
		return;
	}

	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.GetDynamicSpecSourceTags().HasTagExact(InputTag))
		{
			AbilitySpecInputReleased(AbilitySpec);
		}
	}
}
