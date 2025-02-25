// Copyright Hiro

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "CombatAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class COMBAT_API UCombatAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:
	static UCombatAssetManager& Get();

protected:
	virtual void StartInitialLoading() override;
};
