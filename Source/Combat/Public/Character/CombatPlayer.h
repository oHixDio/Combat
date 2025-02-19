// Copyright Hiro

#pragma once

#include "CoreMinimal.h"
#include "CombatCharacterBase.h"
#include "CombatPlayer.generated.h"

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
	// Weapon
	// ====== ====== ======
protected:
	virtual void EquipWeapon(AWeapon* WeaponToEquip) override;

	virtual void OnRep_Weapon() override;

private:
	void EquipMode();
};
