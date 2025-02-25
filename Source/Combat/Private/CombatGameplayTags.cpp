// Copyright Hiro


#include "CombatGameplayTags.h"

#include "GameplayTagsManager.h"

FCombatGameplayTags FCombatGameplayTags::Instance;

void FCombatGameplayTags::InitializeNativeGameplayTags()
{
	Instance.Attributes_Vital_Health = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Vital.Health"), FString("Health decreases when you takes damage. When it reaches 0, you die"));
	Instance.Attributes_Vital_MaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Vital.MaxHealth"), FString("Max health"));
	Instance.Attributes_Vital_Stamina = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Vital.Stamina"), FString("Player consume Stamina when player act motion something"));
	Instance.Attributes_Vital_MaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Vital.MaxStamina"), FString("Max stamina"));

	Instance.Action_Jump = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Action.Jump"), FString("Player act Jump"));
	Instance.Action_Sprint = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Action.Jump"), FString("Player act Sprint"));
	Instance.Action_Crouch = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Action.Jump"), FString("Player act Crouch"));
	Instance.Action_Aim = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Action.Jump"), FString("Player act Aim"));
	Instance.Action_Roll = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Action.Jump"), FString("Player act Roll"));
}
