// Copyright Hiro


#include "UI/Widgets/CombatUserWidget.h"

void UCombatUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}
