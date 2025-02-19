// Copyright Hiro

#pragma once

#include "CoreMinimal.h"
#include "CombatCharacterBase.h"
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
	
	void ToggleCrouch();

	void Sprint();

	void UnSprint();

	void Aim();

	void UnAim();

	void SetSprinting(const bool bSprinting);

	UFUNCTION(Server, Reliable)
	void ServerSetSprinting(const bool bSprinting);

	void SetAiming(const bool bAiming);

	UFUNCTION(Server, Reliable)
	void ServerSetAiming(const bool bAiming);

	// ====== ====== ======
	// Weapon
	// ====== ====== ======
protected:
	virtual void EquipWeapon(AWeapon* WeaponToEquip) override;

	virtual void OnRep_Weapon() override;

private:
	void EquipMode();
};
