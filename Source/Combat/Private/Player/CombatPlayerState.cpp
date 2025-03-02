// Copyright Hiro


#include "Player/CombatPlayerState.h"

#include "AbilitySystem/CombatAbilitySystemComponent.h"
#include "AbilitySystem/CombatAttributeSet.h"

ACombatPlayerState::ACombatPlayerState()
{
	AttributeSet = CreateDefaultSubobject<UCombatAttributeSet>("AttributeSet");
	
	AbilitySystemComponent = CreateDefaultSubobject<UCombatAbilitySystemComponent>("AbilitySystem_Component");
	check(AbilitySystemComponent);
	AbilitySystemComponent->SetIsReplicated(true);
	// Replicationをマルチ and Player-Controlledに設定.
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	// 登録. マルチプレイ環境での適切なレプリケートを目的とする.
	AbilitySystemComponent->AddSpawnedAttribute(AttributeSet);
}

UAbilitySystemComponent* ACombatPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

const UAttributeSet* ACombatPlayerState::GetAttributeSet() const
{
	return AttributeSet;
}
