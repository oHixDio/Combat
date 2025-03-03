// Copyright Hiro


#include "Player/CombatPlayerState.h"

#include "AbilitySystem/CombatAbilitySystemComponent.h"
#include "AbilitySystem/CombatAttributeSet.h"

ACombatPlayerState::ACombatPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UCombatAbilitySystemComponent>("AbilitySystem_Component");
	check(AbilitySystemComponent);
	AbilitySystemComponent->SetIsReplicated(true);
	// Replicationをマルチ and Player-Controlledに設定.
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	// AttributeSetの生成と登録. マルチプレイ環境での適切なレプリケートを目的とする.
	AttributeSet = AbilitySystemComponent->GetSet<UCombatAttributeSet>();
}

UAbilitySystemComponent* ACombatPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

const UAttributeSet* ACombatPlayerState::GetAttributeSet() const
{
	return AttributeSet;
}
