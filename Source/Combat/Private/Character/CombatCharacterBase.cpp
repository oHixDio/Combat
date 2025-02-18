// Copyright Hiro


#include "Character/CombatCharacterBase.h"
#include "Weapon/Weapon.h"
#include "Camera/CameraComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "GameFramework/SpringArmComponent.h"
#include "Net/UnrealNetwork.h"

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

	StartupEquipment();
	
}

void ACombatCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACombatCharacterBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACombatCharacterBase, Weapon);
}

UAbilitySystemComponent* ACombatCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ACombatCharacterBase::InitAbilityActorInfo()
{
	// 
}

void ACombatCharacterBase::OnRep_Weapon()
{
	AttachActorToRightHand(Weapon);
}

void ACombatCharacterBase::StartupEquipment()
{
	if (StartupEquipmentWeapon == nullptr) return;

	Weapon = GetWorld()->SpawnActor<AWeapon>(StartupEquipmentWeapon);
	check(Weapon);
	Weapon->SetOwner(this);	// Repされます.
	AttachActorToRightHand(Weapon);
}

void ACombatCharacterBase::AttachActorToRightHand(AActor* AttachToActor) const
{
	if (AttachToActor == nullptr || GetMesh() == nullptr) return;
	
	if (const USkeletalMeshSocket* RightHandSocket = GetMesh()->GetSocketByName(FName("RightHandSocket")))
	{
		RightHandSocket->AttachActor(AttachToActor,GetMesh());
	}
}

