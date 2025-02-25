// Copyright Hiro

#pragma once

#include "CoreMinimal.h"
#include "CombatCharacterBase.h"
#include "GameplayTagContainer.h"
#include "CombatPlayer.generated.h"

class UInputAction;
class USpringArmComponent;
class UCameraComponent;

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
private:
	UPROPERTY(Category="Combat | Character", VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> SpringArm{};

	UPROPERTY(Category="Combat | Character", VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FollowCamera{};
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
	UPROPERTY(Category="Combat | Input", EditAnywhere)
	TObjectPtr<UInputAction> CrouchAction{};

	UPROPERTY(Category="Combat | Input", EditAnywhere)
	TObjectPtr<UInputAction> SprintAction{};

	UPROPERTY(Category="Combat | Input", EditAnywhere)
	TObjectPtr<UInputAction> JumpAction{};

	UPROPERTY(Category="Combat | Input", EditAnywhere)
	TObjectPtr<UInputAction> AimAction{};

	UPROPERTY(Replicated)
	bool bIsAiming{};

	UPROPERTY(Replicated)
	bool bIsSprinting{};

	UPROPERTY(Category="Combat | Action", EditAnywhere)
	float CrouchWalkSpeed{200.f};

	UPROPERTY(Category="Combat | Action", EditAnywhere)
	float BaseWalkSpeed{500.f};

	UPROPERTY(Category="Combat | Action", EditAnywhere)
	float SPrintWalkSpeed{800.f};

	UPROPERTY(Category="Combat | Action", EditAnywhere)
	float AimWalkSpeed{300.f};

	UPROPERTY(Category="Combat | Action", EditAnywhere)
	float CanSprintVelocity{300.f};

	UPROPERTY(Category="Combat | Action", EditAnywhere)
	float CanSprintAngle{20.f};
	
	UPROPERTY(Category="Combat | Action", EditAnywhere)
	float AimingSpringArmLength{25.f};

	UPROPERTY(Category="Combat | Action", EditAnywhere)
	float SprintingSpringArmLength{100.f};
	
	UPROPERTY(Category="Combat | Action", EditAnywhere)
	float BaseSpringArmLength{50.f};
	
	void ToggleCrouch();

	void Sprint();

	void UnSprint();

	void CheckSprint();

	void Aim();

	void UnAim();

	void SetSprinting(const bool bSprinting);

	UFUNCTION(Server, Reliable)
	void ServerSetSprinting(const bool bSprinting);

	bool CanSprint() const;

	void SetAiming(const bool bAiming);

	UFUNCTION(Server, Reliable)
	void ServerSetAiming(const bool bAiming);

	TArray<FGameplayTag> CurrentActions{};

	// ====== ====== ======
	// Weapon
	// ====== ====== ======
protected:
	virtual void EquipWeapon(AWeapon* WeaponToEquip) override;

	virtual void OnRep_Weapon() override;

private:
	void EquipMode();
};
