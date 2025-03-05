// Copyright Hiro


#include "UI/HUD/CombatHUD.h"

#include "UI/WidgetController/OverlayWidgetController.h"
#include "UI/Widgets/CombatUserWidget.h"

UOverlayWidgetController* ACombatHUD::GetOverlayWidgetController(const FWidgetControllerParams& Params)
{
	if (OverlayWidgetControllerInstance == nullptr)
	{
		check(OverlayWidgetControllerClass);

		OverlayWidgetControllerInstance = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetControllerInstance->SetWidgetControllerParams(Params);
		OverlayWidgetControllerInstance->BindCallbacksToDependencies();
	}

	return OverlayWidgetControllerInstance;
}

void ACombatHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, const UAttributeSet* AS)
{
	check(OverlayWidgetClass);
	OverlayWidget = CreateWidget<UCombatUserWidget>(GetWorld(), OverlayWidgetClass);
	
	const FWidgetControllerParams Params(PC, PS, ASC, AS);
	UOverlayWidgetController* WidgetController = GetOverlayWidgetController(Params);
	WidgetController->BroadcastInitialValues();
	
	check(OverlayWidget)
	OverlayWidget->SetWidgetController(WidgetController);
	OverlayWidget->AddToViewport();
}
