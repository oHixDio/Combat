// Copyright Hiro

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "CombatCharacterBase.generated.h"

class AWeapon;
class UAttributeSet;
class UAbilitySystemComponent;
class USpringArmComponent;
class UCameraComponent;

UCLASS(Abstract)
class COMBAT_API ACombatCharacterBase : public ACharacter, public IAbilitySystemInterface
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
	
private:
	UPROPERTY(Category="Combat | Character", VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> SpringArm{};

	UPROPERTY(Category="Combat | Character", VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FollowCamera{};

	virtual void InitAbilityActorInfo();

	// ====== ====== ======
	// Weapon
	// ====== ====== ======
protected:
	UPROPERTY(Category="Combat | Weapon", EditDefaultsOnly)
	TSubclassOf<AWeapon> StartupEquipmentWeapon{};

	UFUNCTION()
	void OnRep_Weapon();
	
private:
	UPROPERTY(ReplicatedUsing = OnRep_Weapon)
	TObjectPtr<AWeapon> Weapon{};

	void StartupEquipment();

	void AttachActorToRightHand(AActor* AttachToActor) const;

};
