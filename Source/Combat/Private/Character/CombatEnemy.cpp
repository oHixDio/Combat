// Copyright Hiro


#include "Character/CombatEnemy.h"

#include "AbilitySystem/CombatAbilitySystemComponent.h"
#include "AbilitySystem/CombatAttributeSet.h"

ACombatEnemy::ACombatEnemy()
{
	AbilitySystemComponent = CreateDefaultSubobject<UCombatAbilitySystemComponent>("AbilitySystemComponent");
	check(AbilitySystemComponent);
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	AttributeSet = AbilitySystemComponent->GetSet<UCombatAttributeSet>();
}

void ACombatEnemy::BeginPlay()
{
	Super::BeginPlay();

	InitAbilityActorInfo();
}

void ACombatEnemy::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
}
