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
	FGameplayTag Attributes_Vital_Stamina;
	

private:
	static FCombatGameplayTags Instance;
};
