// Copyright 2017 Binary Scroll Interactive

#include "VehicleCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/AudioComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "DesertRoadsGameStateBase.h"
#include "Engine/World.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Math/Color.h"
#include "PaperFlipbookComponent.h"
#include "Sound/SoundCue.h"

AVehicleCharacter::AVehicleCharacter() 
	: Speed(0.5f)
	, MaxFuel(100.0f)
	, FuelConsumeRate (5.0f)
	, EmptyFuelColorization(FLinearColor::Red)
	, FullFuelColorization(FLinearColor::White)
	, bGameOver(false)
{
	// Use only Yaw from the controller and ignore the rest of the rotation.
	bUseControllerRotationYaw = true;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	// Create a camera and attach it to the boom
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(RootComponent);

	// Prevent all automatic rotation behavior on the camera, character, and camera component
	Camera->bUsePawnControlRotation = false;
	Camera->bAutoActivate = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;

	// Behave like a traditional 2D platformer character, with a flat bottom instead of a curved capsule bottom
	// Note: This can cause a little floating when going up inclines; you can choose the tradeoff between better
	// behavior on the edge of a ledge versus inclines by setting this to true or false
	GetCharacterMovement()->bUseFlatBaseForFloorChecks = true;

	VehicleAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("VehicleAudioComponent"));
	VehicleAudioComponent->bAutoActivate = false; // don't play the sound immediately.
	VehicleAudioComponent->SetupAttachment(RootComponent);
}

void AVehicleCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	PlayerInputComponent->BindAxis(TEXT("MoveUp"), this, &AVehicleCharacter::MoveUp);
	PlayerInputComponent->BindAction(TEXT("Quit"), EInputEvent::IE_Released, this, &AVehicleCharacter::Quit);
	
}

void AVehicleCharacter::Quit()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit);
}

void AVehicleCharacter::MoveUp(float Value)
{
	if (bGameOver) { return; }
	AddMovementInput(FVector(0.0f, Speed, 0.0f), Value);
}

void AVehicleCharacter::BeginPlay()
{
	Super::BeginPlay();

	InitFuel();
}

void AVehicleCharacter::Tick(float Delta)
{
	UpdateFuel(-FuelConsumeRate * Delta);
}

void AVehicleCharacter::InitFuel()
{
	// Fuel up!
	CurrentFuel = MaxFuel;
	UpdateFuelVisualization();
	bGameOver = false;
}

void AVehicleCharacter::UpdateFuel(float FuelDelta)
{
	if (bGameOver) { return; }

	CurrentFuel = FMath::Clamp(CurrentFuel + FuelDelta, 0.0f, MaxFuel);
	UpdateFuelVisualization();

	if (CurrentFuel < KINDA_SMALL_NUMBER)
	{
		HandleOutOfFuel();
	}
}

void AVehicleCharacter::TimeUp()
{
	bGameOver = true;
	VehicleAudioComponent->SetSound(TimeUpSound);
	VehicleAudioComponent->Play();
}

void AVehicleCharacter::UpdateFuelVisualization()
{
	CurrentFuelPercentage = CurrentFuel / MaxFuel;
	CurrentFuelColorization = FMath::Lerp(EmptyFuelColorization, FullFuelColorization, CurrentFuelPercentage);
}

void AVehicleCharacter::HandleOutOfFuel()
{
	// Block Input
	bGameOver = true;
	// Stop vehicle flipbook
	GetSprite()->Stop();

	VehicleAudioComponent->SetSound(OutOfFuelSound);
	VehicleAudioComponent->Play();

	if (GetWorld() != nullptr)
	{
		ADesertRoadsGameStateBase* const MyGameState = GetWorld()->GetGameState<ADesertRoadsGameStateBase>();
		if (MyGameState != nullptr)
		{
			MyGameState->HandleGameOver();
		}
	}
}
