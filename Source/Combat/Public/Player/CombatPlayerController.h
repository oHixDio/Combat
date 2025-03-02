// Copyright Hiro

#pragma once

#include "InputActionValue.h"

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/PlayerController.h"
#include "CombatPlayerController.generated.h"

class UCombatAbilitySystemComponent;
class UCombatInputConfig;
class UInputMappingContext;
class UInputAction;

/**
 * 
 */
UCLASS(Abstract)
class COMBAT_API ACombatPlayerController : public APlayerController
{
	GENERATED_BODY()

	// ====== ====== ======
	// Super
	// ====== ====== ======
public:
	ACombatPlayerController();

	virtual void PlayerTick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

	// ====== ====== ======
	// Core
	// ====== ====== ======
protected:
	UCombatAbilitySystemComponent* GetCombatASC();
private:
	UPROPERTY()
	TObjectPtr<UCombatAbilitySystemComponent> CombatASC{};

	// ====== ====== ======
	// Input
	// ====== ====== ======
private:
	UPROPERTY(Category="Combat | Input", EditAnywhere)
	TObjectPtr<UInputMappingContext> CombatContext{};
	
	UPROPERTY(Category="Combat | Input", EditAnywhere)
	TObjectPtr<UInputAction> MoveAction{};
	
	UPROPERTY(Category="Combat | Input", EditAnywhere)
	TObjectPtr<UInputAction> LookAction{};

	UPROPERTY(Category="Combat | Input", EditAnywhere)
	TObjectPtr<UCombatInputConfig> InputConfig{};

	void Move(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);

	void PressedAbilityAction(FGameplayTag InputTag);

	void TriggeredAbilityAction(FGameplayTag InputTag);

	void ReleasedAbilityAction(FGameplayTag InputTag);

};
