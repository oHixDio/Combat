// Copyright Hiro

#pragma once

#include "CoreMinimal.h"
#include "CombatCharacterBase.h"
#include "GameplayTagContainer.h"
#include "Components/TimelineComponent.h"
#include "CombatPlayer.generated.h"

class UInputAction;
class USpringArmComponent;
class UCameraComponent;

template<class T>
using TRuleFuncPtr = bool (T::*)() const;


/**
 * 
 */
UCLASS()
class COMBAT_API ACombatPlayer : public ACombatCharacterBase
{
	GENERATED_BODY()

	// ====== ====== ======
	// Engine
	// ====== ====== ======
public:
	ACombatPlayer();
	
	virtual void PossessedBy(AController* NewController) override;

	virtual void OnRep_PlayerState() override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void Tick(float DeltaTime) override;

	// ====== ====== ======
	// Core
	// ====== ====== ======
protected:
	UFUNCTION(Category="Combat | Character", BlueprintImplementableEvent)
	void ArmTargetLengthSet(const float TargetLength);

	UFUNCTION(Category="Combat | Character", BlueprintImplementableEvent)
	void ArmTargetOffsetSet(const FVector& TargetOffset);
	
private:
	UPROPERTY(Category="Combat | Character", VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> SpringArm{};

	UPROPERTY(Category="Combat | Character", VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FollowCamera{};

	void SetArmTarget(const float TargetLength, const FVector& TargetOffset);
	
	/*
	 * ASC,ASをPlayerStateから受け取り、ASC->InitAbilityActorInfoを実行するハンドル関数.
	 */
	virtual void InitAbilityActorInfo() override;

	// ====== ====== ======
	// Combat Interface
	// ====== ====== ======
public:
	virtual bool IsAiming_Implementation() const override;

	virtual bool IsSprinting_Implementation() const override;

	// ====== ====== ======
	// Action
	// ====== ====== ======
private:
	UPROPERTY(Category="Combat | Action | Input", EditAnywhere)
	TObjectPtr<UInputAction> CrouchAction{};

	UPROPERTY(Category="Combat | Action | Input", EditAnywhere)
	TObjectPtr<UInputAction> SprintAction{};

	UPROPERTY(Category="Combat | Action | Input", EditAnywhere)
	TObjectPtr<UInputAction> JumpAction{};

	UPROPERTY(Category="Combat | Action | Input", EditAnywhere)
	TObjectPtr<UInputAction> AimAction{};

	UPROPERTY(Category="Combat | Action | Walk", EditAnywhere)
	float BaseWalkSpeed{500.f};

	UPROPERTY(Category="Combat | Action | Walk", EditAnywhere)
	float CrouchWalkSpeed{200.f};

	UPROPERTY(Category="Combat | Action | Walk", EditAnywhere)
	float SprintWalkSpeed{800.f};

	UPROPERTY(Category="Combat | Action | Walk", EditAnywhere)
	float AimWalkSpeed{300.f};
	
	UPROPERTY(Category="Combat | Action | Camera", EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	float BaseArmLength{50.f};

	UPROPERTY(Category="Combat | Action | Camera", EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	float SprintingArmLength{100.f};

	UPROPERTY(Category="Combat | Action | Camera", EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	FVector BaseArmOffset{};

	UPROPERTY(Category="Combat | Action | Camera", EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	FVector CrouchArmOffset{FVector(0.f,0.f,-50.f)};
	
	UPROPERTY(Category="Combat | Action | Rule", EditAnywhere)
	float CanSprintVelocity{300.f};

	UPROPERTY(Category="Combat | Action | Rule", EditAnywhere)
	float CanSprintAngle{20.f};

	UPROPERTY(Replicated)
	bool bIsAiming{};

	UPROPERTY(Replicated)
	bool bIsSprinting{};

	/** Do Actions */
	
	void ToggleCrouch();

	void Sprint();

	void UnSprint();

	void Aim();

	void UnAim();

	/** Checker Actions */
	
	void CheckSprint();

	/** Setter */

	void SetIsSprinting(const bool bSprinting);

	UFUNCTION(Server, Reliable)
	void ServerSetIsSprinting(const bool bSprinting);

	void SetIsAiming(const bool bAiming);

	UFUNCTION(Server, Reliable)
	void ServerSetIsAiming(const bool bAiming);

	/** Can Actions */

	bool CanSprint() const;

	bool CanAim() const;

	/*
	 * Applied Actions
	 */

	TArray<FGameplayTag> AppliedActions{};

	TMap<FGameplayTag, TRuleFuncPtr<ACombatPlayer>> ActionRules{};

	void InitializeActionRule();

	void ApplyAction(const FGameplayTag& ApplyActionTag);

	void RemoveAction(const FGameplayTag& RemoveActionTag);

	void ChangeActionMovement(const TArray<FGameplayTag>& Actions);

	bool CanAction(const FGameplayTag& ActionTag) const;

	// ====== ====== ======
	// Weapon
	// ====== ====== ======
protected:
	virtual void EquipWeapon(AWeapon* WeaponToEquip) override;

	virtual void OnRep_Weapon() override;

private:
	void EquipMode();
};
