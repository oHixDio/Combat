// Copyright Hiro

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "CombatInputConfig.generated.h"

class UInputAction;

USTRUCT(BlueprintType)
struct FCombatInputAction
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	const UInputAction* InputAction{};

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag InputTag{};
};


/**
 * 
 */
UCLASS()
class COMBAT_API UCombatInputConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FCombatInputAction> AbilityInputActions{};

	const UInputAction* FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound) const; 
};
