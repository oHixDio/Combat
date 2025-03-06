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
	Instance.Action_Sprint = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Action.Sprint"), FString("Player act Sprint"));
	Instance.Action_Crouch = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Action.Crouch"), FString("Player act Crouch"));
	Instance.Action_Aim = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Action.Aim"), FString("Player act Aim"));
	Instance.Action_Roll = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Action.Roll"), FString("Player act Roll"));

	Instance.Input_Jump = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.Jump"), FString("Input key is Jump"));
	Instance.Input_Sprint = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.Sprint"), FString("Input key is Sprint"));
	Instance.Input_UnSprint = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.UnSprint"), FString("Input key is UnSprint"));
	Instance.Input_Crouch = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.Crouch"), FString("Input key is Crouch"));
	Instance.Input_UnCrouch = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.UnCrouch"), FString("Input key is UnCrouch"));
	Instance.Input_Aim = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.Aim"), FString("Input key is Aim"));
	Instance.Input_UnAim = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.UnAim"), FString("Input key is UnAim"));
	Instance.Input_Roll = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.Roll"), FString("Input key is Roll"));
}
