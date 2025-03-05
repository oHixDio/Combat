// Copyright Hiro

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/WidgetController.h"
#include "OverlayWidgetController.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class COMBAT_API UOverlayWidgetController : public UWidgetController
{
	GENERATED_BODY()

public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;

	UPROPERTY(Category = "Combat | UI", BlueprintAssignable)
	FOnAttributeValueChanged OnStaminaChanged;

	UPROPERTY(Category = "Combat | UI", BlueprintAssignable)
	FOnAttributeValueChanged OnMaxStaminaChanged;
};
