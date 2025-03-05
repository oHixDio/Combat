// Copyright Hiro


#include "Actor/EffectApplier.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

AEffectApplier::AEffectApplier()
{
	PrimaryActorTick.bCanEverTick = false;
	SetRootComponent(CreateDefaultSubobject<USceneComponent>("Root"));
}

void AEffectApplier::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (TargetASC == nullptr) return;	// ← ASCを持っていないActorと接触する可能性がある.

	check(GameplayEffectClass);
	FGameplayEffectContextHandle ContextHandle = TargetASC->MakeEffectContext();
	ContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle SpecHandle = TargetASC->MakeOutgoingSpec(GameplayEffectClass, ApplierLevel, ContextHandle);
	const FActiveGameplayEffectHandle ActiveEffectHandle = TargetASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());

	// 削除するためにキャッシュする。
	const bool bIsInfinite =  EGameplayEffectDurationType::Infinite == SpecHandle.Data.Get()->Def.Get()->DurationPolicy;
	if (bIsInfinite && EEffectRemovalPolicy::RemoveOnEndOverlap == RemovalPolicy)
	{
		ActiveEffectHandles.Add(ActiveEffectHandle, TargetASC);
	}

	if (bAppliedDestroy && !bIsInfinite)
	{
		Destroy();
	}
}

void AEffectApplier::OnBeginOverlap(AActor* TargetActor)
{
	if (EEffectApplicationPolicy::ApplyOnBeginOverlap == ApplicationPolicy)
	{
		ApplyEffectToTarget(TargetActor, ApplyEffectClass);
	}
}

void AEffectApplier::OnEndOverlap(AActor* TargetActor)
{
	if (EEffectApplicationPolicy::ApplyOnEndOverlap == ApplicationPolicy)
	{
		ApplyEffectToTarget(TargetActor, ApplyEffectClass);
	}

	RemoveEffect(TargetActor);
}

void AEffectApplier::RemoveEffect(AActor* TargetActor)
{
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (!IsValid(TargetASC)) return;

	TArray<FActiveGameplayEffectHandle> RemovedEffects;
	
	for (TTuple<FActiveGameplayEffectHandle, UAbilitySystemComponent*> ActiveEffectHandle : ActiveEffectHandles)
	{
		// ApplyしたアクタがEndOverlapしたのかを確かめている。
		if (ActiveEffectHandle.Value == TargetASC)
		{
			// ActiveEffectsから１つずつ除去する。
			TargetASC->RemoveActiveGameplayEffect(ActiveEffectHandle.Key, 1);
			// 後で配列から除去する為にキャッシュする。
			RemovedEffects.Add(ActiveEffectHandle.Key);
		}
	}
	
	// ASCから除去できたHandleをMapからも除去する。
	for (FActiveGameplayEffectHandle& RemovedEffect : RemovedEffects)
	{
		ActiveEffectHandles.FindAndRemoveChecked(RemovedEffect);
	}
}