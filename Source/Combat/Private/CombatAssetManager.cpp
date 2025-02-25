// Copyright Hiro


#include "CombatAssetManager.h"
#include "CombatGameplayTags.h"

UCombatAssetManager& UCombatAssetManager::Get()
{
	check(GEngine);
	return *Cast<UCombatAssetManager>(GEngine->AssetManager);
}

void UCombatAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	FCombatGameplayTags::Get().InitializeNativeGameplayTags();
}
