// Copyright Hiro


#include "Character/CombatPlayer.h"

#include "AbilitySystemComponent.h"
#include "Player/CombatPlayerState.h"

void ACombatPlayer::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	InitAbilityActorInfo();
}

void ACombatPlayer::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	InitAbilityActorInfo();
}

void ACombatPlayer::InitAbilityActorInfo()
{
	ACombatPlayerState* CombatPlayerState = GetPlayerState<ACombatPlayerState>();
	check(CombatPlayerState);
	AbilitySystemComponent = CombatPlayerState->GetAbilitySystemComponent();
	AttributeSet = CombatPlayerState->GetAttributeSet();
	AbilitySystemComponent->InitAbilityActorInfo(CombatPlayerState,this);
}
