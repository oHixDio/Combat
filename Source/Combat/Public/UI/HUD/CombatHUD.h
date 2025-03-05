// Copyright Hiro

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CombatHUD.generated.h"

class UCombatUserWidget;
class UAttributeSet;
class UAbilitySystemComponent;
struct FWidgetControllerParams;
class UOverlayWidgetController;
/**
 * 
 */
UCLASS()
class COMBAT_API ACombatHUD : public AHUD
{
	GENERATED_BODY()
public:
	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& Params);

	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, const UAttributeSet* AS);
	
private:
	UPROPERTY(Category = "Combat", EditAnywhere)
	TSubclassOf<UUserWidget> OverlayWidgetClass{};

	UPROPERTY()
	TObjectPtr<UCombatUserWidget> OverlayWidget{};

	UPROPERTY(Category = "Combat", EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass{};

	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetControllerInstance{};
};
