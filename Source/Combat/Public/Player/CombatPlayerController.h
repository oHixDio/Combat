// Copyright Hiro

#pragma once

#include "InputActionValue.h"

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CombatPlayerController.generated.h"

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
	// Input
	// ====== ====== ======
private:
	UPROPERTY(Category="Combat | Input", EditAnywhere)
	TObjectPtr<UInputMappingContext> CombatContext{};
	
	UPROPERTY(Category="Combat | Input", EditAnywhere)
	TObjectPtr<UInputAction> MoveAction{};
	
	UPROPERTY(Category="Combat | Input", EditAnywhere)
	TObjectPtr<UInputAction> LookAction{};

	void Move(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);

};
