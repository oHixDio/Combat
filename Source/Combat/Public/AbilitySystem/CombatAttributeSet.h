// Copyright Hiro

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "CombatAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

USTRUCT(BlueprintType)
struct FEffectProperties
{
	GENERATED_BODY()

	FEffectProperties(){}
	FEffectProperties(
		FGameplayEffectContextHandle EffectContextHandle,
		UAbilitySystemComponent* SASC, AActor* SAA, AController* SController, ACharacter* SCharacter,
		UAbilitySystemComponent* TASC, AActor* TAA, AController* TController, ACharacter* TCharacter)
		: GameplayEffectContextHandle(EffectContextHandle),
		  SourceASC(SASC), SourceAvatarActor(SAA), SourceController(SController), SourceCharacter(SCharacter),
		  TargetASC(TASC), TargetAvatarActor(TAA), TargetController(TController), TargetCharacter(TCharacter){}

	UPROPERTY()
	FGameplayEffectContextHandle GameplayEffectContextHandle{};
	
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> SourceASC{};

	UPROPERTY()
	TObjectPtr<AActor> SourceAvatarActor{};

	UPROPERTY()
	TObjectPtr<AController> SourceController{};

	UPROPERTY()
	TObjectPtr<ACharacter> SourceCharacter{};
	
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> TargetASC{};

	UPROPERTY()
	TObjectPtr<AActor> TargetAvatarActor{};
	
	UPROPERTY()
	TObjectPtr<AController> TargetController{};

	UPROPERTY()
	TObjectPtr<ACharacter> TargetCharacter{};
};

template<class T>
using TStaticFuncPtr = typename TBaseStaticDelegateInstance<T, FDefaultDelegateUserPolicy>::FFuncPtr;


/**
 * 
 */
UCLASS()
class COMBAT_API UCombatAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UCombatAttributeSet();

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

private:
	void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const;

public:
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "Combat | Attribute | Vital")
	FGameplayAttributeData Health; ATTRIBUTE_ACCESSORS(UCombatAttributeSet, Health)
	UFUNCTION() void OnRep_Health(const FGameplayAttributeData& OldHealth) const;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "Combat | Attribute | Vital")
	FGameplayAttributeData MaxHealth; ATTRIBUTE_ACCESSORS(UCombatAttributeSet, MaxHealth)
	UFUNCTION() void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Stamina, Category = "Combat | Attribute | Vital")
	FGameplayAttributeData Stamina; ATTRIBUTE_ACCESSORS(UCombatAttributeSet, Stamina)
	UFUNCTION() void OnRep_Stamina(const FGameplayAttributeData& OldStamina) const;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxStamina, Category = "Combat | Attribute | Vital")
	FGameplayAttributeData MaxStamina; ATTRIBUTE_ACCESSORS(UCombatAttributeSet, MaxStamina)
	UFUNCTION() void OnRep_MaxStamina(const FGameplayAttributeData& OldMaxStamina) const;


};
