
#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "CombatPlayerState.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class COMBAT_API ACombatPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

	// ====== ====== ======
	// Engine
	// ====== ====== ======
public:
	ACombatPlayerState();

	// ====== ====== ======
	// Core
	// ====== ====== ======
public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UAttributeSet* GetAttributeSet();
private:
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent{};

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet{};

	
	
};
