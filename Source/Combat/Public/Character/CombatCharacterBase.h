// Copyright Hiro

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "CombatCharacterBase.generated.h"

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

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

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
	
};
