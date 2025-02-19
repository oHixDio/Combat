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
	GetCharacterMovement()->MaxWalkSpeed = BaseWalkSpeed;
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

void ACombatPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsLocallyControlled())
	{
		CheckSprint();
	}
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
		
		if (bIsAiming)
		{
			SetMovementSpeed(AimWalkSpeed);
		}
		else
		{
			SetMovementSpeed(BaseWalkSpeed);
		}
	}
	else
	{
		Crouch();
		SetMovementSpeed(CrouchWalkSpeed);
	}
}

void ACombatPlayer::Sprint()
{
	if (CanSprint())
	{
		SetSprinting(true);
		SetMovementSpeed(SPrintWalkSpeed);
	}
}

void ACombatPlayer::UnSprint()
{
	if (bIsSprinting)
	{
		SetSprinting(false);
		SetMovementSpeed(BaseWalkSpeed);
	}
}

bool ACombatPlayer::CanSprint() const
{
	/*
	 * 条件
	 * 1, 前方に進んでいるか？
	 * 2, Sprintできる速度に達しているか？
	 */
	
	FVector Velocity = GetVelocity();
	const FVector Forward = GetActorForwardVector();
	Velocity.Normalize();
	// 正規化された値同士で内積を求める.
	const float DotProduct = FVector::DotProduct(Velocity, Forward);
	const float ArcCos = FMath::Acos(DotProduct);	// Acosの結果はラジアン値.
	// 角度を求める.
	const float AngleDegrees = FMath::RadiansToDegrees(ArcCos);
	
	// 現在の速度を取得.
	const float CurrentVelocity = GetVelocity().Size();

	// Debug.
	if (HasAuthority() && IsLocallyControlled())
	{
		GEngine->AddOnScreenDebugMessage(1, 1.f, FColor::Blue, FString::Printf(TEXT("Degrees: %f"), AngleDegrees));
		GEngine->AddOnScreenDebugMessage(2, 1.f, FColor::Blue, FString::Printf(TEXT("Velocity: %f"), CurrentVelocity));
	}

	// 1の判定.
	const bool bSuccessAngle = AngleDegrees <= CanSprintAngle;
	
	// 2の判定.
	const bool bSuccessVelocity = CurrentVelocity >= CanSprintVelocity;

	return bSuccessAngle && bSuccessVelocity;
}


void ACombatPlayer::CheckSprint()
{
	if (bIsSprinting && !CanSprint())
	{
		UnSprint();
	}
}

void ACombatPlayer::Aim()
{
	SetAiming(true);
	if (bIsSprinting)
	{
		UnSprint();
	}
	SetMovementSpeed(AimWalkSpeed);
}

void ACombatPlayer::UnAim()
{
	SetAiming(false);
	SetMovementSpeed(BaseWalkSpeed);
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

