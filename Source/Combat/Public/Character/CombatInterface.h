// Copyright Hiro

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CombatInterface.generated.h"

class AWeapon;

UINTERFACE(MinimalAPI)
class UCombatInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class COMBAT_API ICombatInterface
{
	GENERATED_BODY()

	
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool IsAiming() const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool IsSprinting() const;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool IsEquippedWeapon() const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	AWeapon* GetWeapon();
};
