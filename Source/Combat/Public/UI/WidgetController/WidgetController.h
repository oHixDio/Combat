// Copyright Hiro

#pragma once

#include "CoreMinimal.h"
#include "WidgetController.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeValueChanged, float, NewValue);

USTRUCT(BlueprintType)
struct FWidgetControllerParams
{
	GENERATED_BODY()

	FWidgetControllerParams() {}
	FWidgetControllerParams(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, const UAttributeSet* AS)
		: PlayerController(PC)
		, PlayerState(PS)
		, AbilitySystemComponent(ASC)
		, AttributeSet(AS)
	{}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<APlayerController> PlayerController{};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<APlayerState> PlayerState{};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent{};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<const UAttributeSet> AttributeSet{};
};

/**
 * 
 */
UCLASS()
class COMBAT_API UWidgetController : public UObject
{
	GENERATED_BODY()
	
public:
	void SetWidgetControllerParams(const FWidgetControllerParams& WidgetControllerParams);

	UFUNCTION(BlueprintCallable)
	virtual void BroadcastInitialValues();
	
	virtual void BindCallbacksToDependencies();

protected:
	UPROPERTY(Category = "Combat | UI", BlueprintReadOnly)
	TObjectPtr<APlayerController> PlayerController{};

	UPROPERTY(Category = "Combat | UI", BlueprintReadOnly)
	TObjectPtr<APlayerState> PlayerState{};

	UPROPERTY(Category = "Combat | UI", BlueprintReadOnly)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent{};

	UPROPERTY(Category = "Combat | UI", BlueprintReadOnly)
	TObjectPtr<const UAttributeSet> AttributeSet{};
};
