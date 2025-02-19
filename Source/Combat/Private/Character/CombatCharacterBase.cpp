// Copyright Hiro


#include "Character/CombatCharacterBase.h"
#include "Weapon/Weapon.h"
#include "Engine/SkeletalMeshSocket.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Net/UnrealNetwork.h"

ACombatCharacterBase::ACombatCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	GetCharacterMovement()->NavAgentProps.bCanCrouch = true;
}

void ACombatCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		StartupEquipment();
	}
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

bool ACombatCharacterBase::IsEquippedWeapon_Implementation() const
{
	return IsValid(Weapon);
}

AWeapon* ACombatCharacterBase::GetWeapon_Implementation()
{
	return Weapon;
}

void ACombatCharacterBase::OnRep_Weapon()
{
	AttachActorToRightHand(Weapon);
}

void ACombatCharacterBase::StartupEquipment()
{
	if (!IsValid(StartupEquipmentWeapon)) return;

	AWeapon* StartupWeapon = GetWorld()->SpawnActor<AWeapon>(StartupEquipmentWeapon);
	check(StartupWeapon);
	EquipWeapon(StartupWeapon);
	
}

void ACombatCharacterBase::AttachActorToRightHand(AActor* AttachToActor) const
{
	if (!IsValid(AttachToActor) || !IsValid(GetMesh())) return;
	
	if (const USkeletalMeshSocket* RightHandSocket = GetMesh()->GetSocketByName(FName("RightHandSocket")))
	{
		RightHandSocket->AttachActor(AttachToActor,GetMesh());
	}
}

void ACombatCharacterBase::EquipWeapon(AWeapon* WeaponToEquip)
{
	if (!IsValid(WeaponToEquip)) return;

	Weapon = WeaponToEquip;
	Weapon->SetOwner(this);	// Repされます.
	AttachActorToRightHand(Weapon);
}

