// Copyright 2017 Binary Scroll Interactive

#include "PowerUp.h"
#include "Components/AudioComponent.h"
#include "Components/CapsuleComponent.h"
#include "PaperFlipbookComponent.h"
#include "Sound/SoundCue.h"
#include "VehicleCharacter.h"

APowerUp::APowerUp()
	: Speed(1.0f)
	, Fuel(5.0f)
{
	PowerUpAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("PowerUpAudioComponent"));
	PowerUpAudioComponent->bAutoActivate = false; // don't play the sound immediately.
	PowerUpAudioComponent->SetupAttachment(RootComponent);
}

void APowerUp::BeginPlay()
{
	Super::BeginPlay();

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &APowerUp::OnOverlapBegin);
}

void APowerUp::Tick(float Delta)
{
	AddMovementInput(FVector::ForwardVector, -Speed * Delta);
}

void APowerUp::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Other Actor is the actor that triggered the event. Check that is not ourself.  
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		AVehicleCharacter* vehicle = Cast<AVehicleCharacter>(OtherActor);
		if (vehicle != nullptr)
		{
			vehicle->UpdateFuel(Fuel);
			PowerUpAudioComponent->SetSound(PowerUpSound);
			PowerUpAudioComponent->Play();
			GetSprite()->SetSpriteColor(FLinearColor::Transparent);
		}
	}
}
