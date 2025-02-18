// Copyright Hiro


#include "Character/CombatCharacterBase.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

ACombatCharacterBase::ACombatCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(RootComponent);

	FollowCamera = CreateDefaultSubobject<UCameraComponent>("FollowCamera");
	FollowCamera->SetupAttachment(SpringArm);
}

void ACombatCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACombatCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

UAbilitySystemComponent* ACombatCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ACombatCharacterBase::InitAbilityActorInfo()
{
	// 
}

