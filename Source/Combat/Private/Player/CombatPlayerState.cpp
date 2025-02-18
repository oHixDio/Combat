// Copyright Hiro


#include "Player/CombatPlayerState.h"

#include "AbilitySystem/CombatAbilitySystemComponent.h"
#include "AbilitySystem/CombatAttributeSet.h"

ACombatPlayerState::ACombatPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UCombatAbilitySystemComponent>("AbilitySystem_Component");
	AbilitySystemComponent->SetIsReplicated(true);
	// Replicationをマルチ and Player-Controlledに設定.
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	
	AttributeSet = CreateDefaultSubobject<UCombatAttributeSet>("AttributeSet");
}

UAbilitySystemComponent* ACombatPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAttributeSet* ACombatPlayerState::GetAttributeSet()
{
	return AttributeSet;
}
