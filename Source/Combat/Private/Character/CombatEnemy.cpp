// Copyright Hiro


#include "Character/CombatEnemy.h"

#include "AbilitySystem/CombatAbilitySystemComponent.h"

ACombatEnemy::ACombatEnemy()
{
	AbilitySystemComponent = CreateDefaultSubobject<UCombatAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<UAttributeSet>("AttributeSet");
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
