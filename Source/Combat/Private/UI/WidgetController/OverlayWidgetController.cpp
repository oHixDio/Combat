// Copyright Hiro


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/CombatAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	const UCombatAttributeSet* CombatAttributeSet = CastChecked<UCombatAttributeSet>(AttributeSet);

	OnStaminaChanged.Broadcast(CombatAttributeSet->GetStamina());
	OnMaxStaminaChanged.Broadcast(CombatAttributeSet->GetMaxStamina());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	const UCombatAttributeSet* CombatAttributeSet = CastChecked<UCombatAttributeSet>(AttributeSet);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(CombatAttributeSet->GetStaminaAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnStaminaChanged.Broadcast(Data.NewValue);
		}
	);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(CombatAttributeSet->GetMaxStaminaAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnMaxStaminaChanged.Broadcast(Data.NewValue);
		}
	);
}
