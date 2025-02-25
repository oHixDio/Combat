// Copyright Hiro

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "CombatInterface.h"
#include "GameFramework/Character.h"
#include "CombatCharacterBase.generated.h"

class UGameplayEffect;
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

	virtual UAttributeSet* GetAttributeSet() const;
	
protected:
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent{};

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet{};

	/** 子クラスの仕様に沿った方法で、ASCのInitAbilityActorInfoを呼び出すラップ関数. */
	virtual void InitAbilityActorInfo();

	void SetMovementSpeed(const float Speed);

	UFUNCTION(Server, Reliable)
	void ServerSetMovementSpeed(const float Speed);

	// ====== ====== ======
	// Combat Interface
	// ====== ====== ======
public:
	virtual bool IsEquippedWeapon_Implementation() const override;

	virtual AWeapon* GetWeapon_Implementation() override;
	
	// ====== ====== ======
	// Weapon
	// ====== ====== ======
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

	// ====== ====== ======
	// Effects
	// ====== ====== ======
public:
	/** 自分自身にEffectを与える. */
	void ApplyEffectToSelf(const TSubclassOf<UGameplayEffect>& EffectClass, const float AbilityLevel) const;
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Combat | Effects")
	TSubclassOf<UGameplayEffect> DefaultVitalAttributeClass{};
	
	void ApplyDefaultAttributes() const;
};
