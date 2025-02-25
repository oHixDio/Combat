// Copyright Hiro


#include "CombatGameplayTags.h"

#include "GameplayTagsManager.h"

FCombatGameplayTags FCombatGameplayTags::Instance;

void FCombatGameplayTags::InitializeNativeGameplayTags()
{
	Instance.Attributes_Vital_Health = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Vital.Health"), FString("Health decreases when you takes damage. When it reaches 0, you die"));
	Instance.Attributes_Vital_Stamina = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Vital.Stamina"), FString("Player consume Stamina when player act motion something"));
}
