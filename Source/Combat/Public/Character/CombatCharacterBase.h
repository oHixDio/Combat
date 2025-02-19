// Copyright Hiro

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "CombatInterface.h"
#include "GameFramework/Character.h"
#include "CombatCharacterBase.generated.h"

class AWeapon;
class UAttributeSet;
class UAbilitySystemComponent;


UCLASS(Abstract)
class COMBAT_API ACombatCharacterBase : public ACharacter, public IAbilitySystemInterface, public ICombatInterface
{
	GENERATED_BODY()

	// ====== ====== ======
	// Engine
	// ====== ====== ======
public:
	ACombatCharacterBase();

	virtual void Tick(float DeltaTime) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
protected:
	virtual void BeginPlay() override;

	// ====== ====== ======
	// Core
	// ====== ====== ======
public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
protected:
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent{};

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet{};

	virtual void InitAbilityActorInfo();

	// ====== ====== ======
	// Core
	// ====== ====== ======
public:
	virtual bool IsEquippedWeapon_Implementation() const override;

	// ====== ====== ======
	// Weapon
	// ====== ====== ======
public:
	virtual AWeapon* GetWeapon_Implementation() override;
protected:
	UPROPERTY(Category="Combat | Weapon", EditDefaultsOnly)
	TSubclassOf<AWeapon> StartupEquipmentWeapon{};

	UFUNCTION()
	virtual void OnRep_Weapon();
	
	virtual void EquipWeapon(AWeapon* WeaponToEquip);
	
private:
	UPROPERTY(ReplicatedUsing = OnRep_Weapon)
	TObjectPtr<AWeapon> Weapon{};

	void StartupEquipment();

	void AttachActorToRightHand(AActor* AttachToActor) const;


};
