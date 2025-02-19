// Copyright Hiro


#include "Character/CombatPlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "AbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/CombatPlayerState.h"

ACombatPlayer::ACombatPlayer()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(GetMesh());
	SpringArm->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>("FollowCamera");
	FollowCamera->SetupAttachment(SpringArm);
	FollowCamera->bUsePawnControlRotation = false;
	
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->NavAgentProps.bCanCrouch = true;
}

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

void ACombatPlayer::EquipWeapon(AWeapon* WeaponToEquip)
{
	Super::EquipWeapon(WeaponToEquip);

	EquipMode();
}

void ACombatPlayer::OnRep_Weapon()
{
	Super::OnRep_Weapon();
	
	EquipMode();
}

void ACombatPlayer::EquipMode()
{
	GetCharacterMovement()->bOrientRotationToMovement = false;
	bUseControllerRotationYaw = true;
}

