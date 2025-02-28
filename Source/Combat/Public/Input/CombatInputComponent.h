// Copyright Hiro

#pragma once

#include "CoreMinimal.h"
#include "CombatInputConfig.h"
#include "EnhancedInputComponent.h"
#include "CombatInputComponent.generated.h"


/**
 * 
 */
UCLASS()
class COMBAT_API UCombatInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	template<class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename TriggeredFuncType>
	void BindAbilityActions(const UCombatInputConfig* InputConfig, UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, TriggeredFuncType TriggeredFunc);
};

template <class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename TriggeredFuncType>
void UCombatInputComponent::BindAbilityActions(const UCombatInputConfig* InputConfig, UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, TriggeredFuncType TriggeredFunc)
{
	check(InputConfig);

	for (const FCombatInputAction& Action : InputConfig->AbilityInputActions)
	{
		if (PressedFunc)
		{
			BindAction(Action.InputAction, ETriggerEvent::Started, Object, PressedFunc, Action.InputTag);
		}
		if (ReleasedFunc)
		{
			BindAction(Action.InputAction, ETriggerEvent::Completed, Object, ReleasedFunc, Action.InputTag);
		}
		if (TriggeredFunc)
		{
			BindAction(Action.InputAction, ETriggerEvent::Triggered, Object, TriggeredFunc, Action.InputTag);
		}
	}
}
