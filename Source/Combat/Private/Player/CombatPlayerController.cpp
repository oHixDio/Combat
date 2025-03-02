// Copyright Hiro


#include "Player/CombatPlayerController.h"
#include "AbilitySystem/CombatAbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Input/CombatInputComponent.h"

ACombatPlayerController::ACombatPlayerController()
{
	bReplicates = true;
}

void ACombatPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
}

void ACombatPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// IMCの設定.
	check(CombatContext);
	if (UEnhancedInputLocalPlayerSubsystem* EnhancedSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		EnhancedSubsystem->AddMappingContext(CombatContext, 0);
	}
}

void ACombatPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UCombatInputComponent* CombatInputComponent = CastChecked<UCombatInputComponent>(InputComponent);
	CombatInputComponent->BindAction(MoveAction.Get(), ETriggerEvent::Triggered, this, &ThisClass::Move);
	CombatInputComponent->BindAction(LookAction.Get(), ETriggerEvent::Triggered, this, &ThisClass::Look);
	CombatInputComponent->BindAbilityActions(InputConfig, this, &ThisClass::PressedAbilityAction, &ThisClass::ReleasedAbilityAction, &ThisClass::TriggeredAbilityAction);
}

UCombatAbilitySystemComponent* ACombatPlayerController::GetCombatASC()
{
	if (CombatASC == nullptr)
	{
		CombatASC = Cast<UCombatAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn()));
	}

	return CombatASC;
}

void ACombatPlayerController::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X));
	const FVector RightDirection(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y));

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, MovementVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ACombatPlayerController::Look(const FInputActionValue& Value)
{
	const FVector2D LookVector = Value.Get<FVector2D>();

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddControllerYawInput(LookVector.X);
		ControlledPawn->AddControllerPitchInput(LookVector.Y);
	}
}

void ACombatPlayerController::PressedAbilityAction(FGameplayTag InputTag)
{
	if (GetCombatASC() == nullptr) return;
	GetCombatASC()->PressedAbilityAction(InputTag);
}

void ACombatPlayerController::TriggeredAbilityAction(FGameplayTag InputTag)
{
	if (GetCombatASC() == nullptr) return;
	GetCombatASC()->TriggeredAbilityAction(InputTag);
}

void ACombatPlayerController::ReleasedAbilityAction(FGameplayTag InputTag)
{
	if (GetCombatASC() == nullptr) return;
	GetCombatASC()->ReleasedAbilityAction(InputTag);
}
