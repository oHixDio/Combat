// Copyright Hiro


#include "Character/CombatCharacterBase.h"

#include "AbilitySystemComponent.h"
#include "GameplayEffectTypes.h"
#include "Weapon/Weapon.h"
#include "Engine/SkeletalMeshSocket.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Net/UnrealNetwork.h"

ACombatCharacterBase::ACombatCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;
	SetNetUpdateFrequency(66.f);
	SetMinNetUpdateFrequency(33.f);

	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;
	GetCharacterMovement()->NavAgentProps.bCanCrouch = true;

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
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

UAttributeSet* ACombatCharacterBase::GetAttributeSet() const
{
	return AttributeSet;
}

void ACombatCharacterBase::InitAbilityActorInfo()
{
	// 純粋仮想関数のように振る舞う.
}

void ACombatCharacterBase::SetMovementSpeed(const float Speed)
{
	GetCharacterMovement()->MaxWalkSpeed = Speed;
	if (!HasAuthority())
	{
		ServerSetMovementSpeed(Speed);
	}
}

void ACombatCharacterBase::ServerSetMovementSpeed_Implementation(const float Speed)
{
	GetCharacterMovement()->MaxWalkSpeed = Speed;
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

void ACombatCharacterBase::ApplyEffectToSelf(const TSubclassOf<UGameplayEffect>& EffectClass, const float AbilityLevel) const
{
	check(GetAbilitySystemComponent());
	check(EffectClass);
	FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	ContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(EffectClass, AbilityLevel, ContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
}

void ACombatCharacterBase::ApplyDefaultAttributes() const
{
	ApplyEffectToSelf(DefaultVitalAttributeClass, 1.f);
}
