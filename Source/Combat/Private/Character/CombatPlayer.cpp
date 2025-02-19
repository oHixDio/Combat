// Copyright Hiro


#include "Character/CombatPlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "AbilitySystemComponent.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Net/UnrealNetwork.h"
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

void ACombatPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Started, this, &ThisClass::ToggleCrouch);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &ACombatPlayer::Sprint);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &ACombatPlayer::UnSprint);
		EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Started, this, &ACombatPlayer::Aim);
		EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Completed, this, &ACombatPlayer::UnAim);
	}
}

void ACombatPlayer::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACombatPlayer, bIsAiming);
	DOREPLIFETIME(ACombatPlayer, bIsSprinting);
}

void ACombatPlayer::InitAbilityActorInfo()
{
	ACombatPlayerState* CombatPlayerState = GetPlayerState<ACombatPlayerState>();
	check(CombatPlayerState);
	AbilitySystemComponent = CombatPlayerState->GetAbilitySystemComponent();
	AttributeSet = CombatPlayerState->GetAttributeSet();
	AbilitySystemComponent->InitAbilityActorInfo(CombatPlayerState,this);
}

bool ACombatPlayer::IsAiming_Implementation() const
{
	return bIsAiming;
}

bool ACombatPlayer::IsSprinting_Implementation() const
{
	return bIsSprinting;
}

void ACombatPlayer::ToggleCrouch()
{
	if (bIsCrouched)
	{
		UnCrouch();
	}
	else
	{
		Crouch();
	}
}

void ACombatPlayer::Sprint()
{
	SetSprinting(true);
}

void ACombatPlayer::UnSprint()
{
	SetSprinting(false);
}

void ACombatPlayer::Aim()
{
	SetAiming(true);
}

void ACombatPlayer::UnAim()
{
	SetAiming(false);
}

void ACombatPlayer::SetSprinting(const bool bSprinting)
{
	bIsSprinting = bSprinting;
	if (!HasAuthority())
	{
		ServerSetSprinting(bSprinting);
	}
}

void ACombatPlayer::ServerSetSprinting_Implementation(const bool bSprinting)
{
	bIsSprinting = bSprinting;
}

void ACombatPlayer::SetAiming(const bool bAiming)
{
	bIsAiming = bAiming;
	if (!HasAuthority())
	{
		ServerSetAiming(bAiming);
	}
}

void ACombatPlayer::ServerSetAiming_Implementation(const bool bAiming)
{
	bIsAiming = bAiming;
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

