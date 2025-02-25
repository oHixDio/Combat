// Copyright Hiro


#include "Character/CombatPlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "AbilitySystemComponent.h"
#include "CombatGameplayTags.h"
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

	InitializeActionRule();
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

void ACombatPlayer::SetArmTarget(const float TargetLength, const FVector& TargetOffset)
{
	ArmTargetLengthSet(TargetLength);
	ArmTargetOffsetSet(TargetOffset);
}

void ACombatPlayer::InitAbilityActorInfo()
{
	ACombatPlayerState* CombatPlayerState = GetPlayerState<ACombatPlayerState>();
	check(CombatPlayerState);
	AbilitySystemComponent = CombatPlayerState->GetAbilitySystemComponent();
	AttributeSet = CombatPlayerState->GetAttributeSet();
	AbilitySystemComponent->InitAbilityActorInfo(CombatPlayerState,this);

	ApplyDefaultAttributes();
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
			SetArmTarget(BaseArmLength, BaseArmOffset);
		}
	}
	else
	{
		Crouch();
		SetMovementSpeed(CrouchWalkSpeed);
		SetArmTarget(BaseArmLength, CrouchArmOffset);
	}
}

void ACombatPlayer::Sprint()
{
	const FCombatGameplayTags& CombatTags = FCombatGameplayTags::Get();
	if (CanAction(CombatTags.Action_Sprint))
	{
		// ApplyAction(CombatTags.Action_Sprint);
		// ChangeActionMovement(AppliedActions);
	}
	
	if (CanSprint())
	{
		SetIsSprinting(true);
		SetMovementSpeed(SprintWalkSpeed);
		SetArmTarget(SprintingArmLength, BaseArmOffset);
	}
}

void ACombatPlayer::UnSprint()
{
	if (bIsSprinting)
	{
		SetIsSprinting(false);
		SetMovementSpeed(BaseWalkSpeed);
		SetArmTarget(BaseArmLength, BaseArmOffset);
	}
}

void ACombatPlayer::Aim()
{
	SetIsAiming(true);
	if (bIsSprinting)
	{
		UnSprint();
	}
	SetMovementSpeed(AimWalkSpeed);
}

void ACombatPlayer::UnAim()
{
	SetIsAiming(false);
	SetMovementSpeed(BaseWalkSpeed);
}

void ACombatPlayer::CheckSprint()
{
	if (bIsSprinting && !CanSprint())
	{
		UnSprint();
	}
}

void ACombatPlayer::SetIsSprinting(const bool bSprinting)
{
	bIsSprinting = bSprinting;
	if (!HasAuthority())
	{
		ServerSetIsSprinting(bSprinting);
	}
}

void ACombatPlayer::ServerSetIsSprinting_Implementation(const bool bSprinting)
{
	bIsSprinting = bSprinting;
}

void ACombatPlayer::SetIsAiming(const bool bAiming)
{
	bIsAiming = bAiming;
	if (!HasAuthority())
	{
		ServerSetIsAiming(bAiming);
	}
}

void ACombatPlayer::ServerSetIsAiming_Implementation(const bool bAiming)
{
	bIsAiming = bAiming;
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

bool ACombatPlayer::CanAim() const
{
	return true;
}

void ACombatPlayer::InitializeActionRule()
{
	const FCombatGameplayTags& CombatTags = FCombatGameplayTags::Get();
	ActionRules.Add(CombatTags.Action_Jump, &ThisClass::CanJump);
	ActionRules.Add(CombatTags.Action_Sprint, &ThisClass::CanSprint);
	ActionRules.Add(CombatTags.Action_Aim, &ThisClass::CanAim);
	ActionRules.Add(CombatTags.Action_Crouch, &ThisClass::CanCrouch);
}

void ACombatPlayer::ApplyAction(const FGameplayTag& ApplyActionTag)
{
	AppliedActions.Add(ApplyActionTag);
}

void ACombatPlayer::RemoveAction(const FGameplayTag& RemoveActionTag)
{
	AppliedActions.Remove(RemoveActionTag);
}

void ACombatPlayer::ChangeActionMovement(const TArray<FGameplayTag>& Actions)
{
	if (Actions.IsEmpty())
	{
		SetMovementSpeed(BaseWalkSpeed);
		return;
	}
	const FCombatGameplayTags& CombatTags = FCombatGameplayTags::Get();
	
	if (Actions.Contains(CombatTags.Action_Aim))
	{
		
	}
	if (Actions.Contains(CombatTags.Action_Aim))
	{
		
	}
	if (Actions.Contains(CombatTags.Action_Aim))
	{
		
	}
	if (Actions.Contains(CombatTags.Action_Aim))
	{
		
	}

	
}

bool ACombatPlayer::CanAction(const FGameplayTag& ActionTag) const
{
	return AppliedActions.Contains(ActionTag) && (this->*ActionRules[ActionTag])();
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
