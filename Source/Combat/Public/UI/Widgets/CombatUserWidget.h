// Copyright Hiro

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CombatUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class COMBAT_API UCombatUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(Category = "Combat | UI", BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController{};

	UFUNCTION(Category = "Combat | UI", BlueprintCallable)
	void SetWidgetController(UObject* InWidgetController);

	UFUNCTION(Category = "Combat | UI", BlueprintImplementableEvent)
	void WidgetControllerSet();
};
