// Copyright Hiro

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 * シングルトンで、ネイティブGameplayTagを構築する.
 */
struct FCombatGameplayTags
{
public:
	static const FCombatGameplayTags& Get() { return Instance; };

	static void InitializeNativeGameplayTags();

	FGameplayTag Attributes_Vital_Health;
	FGameplayTag Attributes_Vital_MaxHealth;
	FGameplayTag Attributes_Vital_Stamina;
	FGameplayTag Attributes_Vital_MaxStamina;

	FGameplayTag Action_Jump;
	FGameplayTag Action_Sprint;
	FGameplayTag Action_Crouch;
	FGameplayTag Action_Aim;
	FGameplayTag Action_Roll;
	

private:
	static FCombatGameplayTags Instance;
};
