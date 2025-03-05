// Copyright Hiro

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayEffectTypes.h"
#include "EffectApplier.generated.h"

class UAbilitySystemComponent;
class UGameplayEffect;
class USphereComponent;

UENUM(BlueprintType)
enum class EEffectApplicationPolicy : uint8
{
	DoNotApply,
	ApplyOnBeginOverlap,
	ApplyOnEndOverlap
};

UENUM(BlueprintType)
enum class EEffectRemovalPolicy : uint8
{
	DoNotRemoval,
	RemoveOnEndOverlap
};

UCLASS()
class COMBAT_API AEffectApplier : public AActor
{
	GENERATED_BODY()
	
public:	
	AEffectApplier();

protected:
	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass);

	UFUNCTION(BlueprintCallable)
	void OnBeginOverlap(AActor* TargetActor);

	UFUNCTION(BlueprintCallable)
	void OnEndOverlap(AActor* TargetActor);
	
private:
	UPROPERTY(Category = "Combat", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UGameplayEffect> ApplyEffectClass{};

	UPROPERTY(Category = "Combat", EditAnywhere)
	EEffectApplicationPolicy ApplicationPolicy{ EEffectApplicationPolicy::DoNotApply };

	UPROPERTY(Category = "Combat", EditAnywhere)
	EEffectRemovalPolicy RemovalPolicy{ EEffectRemovalPolicy::RemoveOnEndOverlap };

	TMap<FActiveGameplayEffectHandle, UAbilitySystemComponent*> ActiveEffectHandles;

	UPROPERTY(Category = "Combat", EditAnywhere)
	float ApplierLevel{ 1.f };

	UPROPERTY(Category = "Combat", EditAnywhere)
	bool bAppliedDestroy{false};

	void RemoveEffect(AActor* TargetActor);
};
