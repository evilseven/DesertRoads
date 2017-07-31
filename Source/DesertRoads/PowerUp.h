// Copyright 2017 Binary Scroll Interactive

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "PowerUp.generated.h"

/**
 * 
 */
UCLASS()
class DESERTROADS_API APowerUp : public APaperCharacter
{
	GENERATED_BODY()
	
private:

	UPROPERTY(Category = "Movement", EditDefaultsOnly)
	float Speed;

	UPROPERTY(Category = "Power Up", EditDefaultsOnly)
	float Fuel;

	UPROPERTY(Category = "Audio", EditDefaultsOnly)
	class USoundCue* PowerUpSound;

	UPROPERTY(Category = "Audio", EditDefaultsOnly)
	class UAudioComponent* PowerUpAudioComponent;

public:

	float GetFuel() const { return Fuel; }

	APowerUp();
	virtual void BeginPlay() override;
	virtual void Tick(float Delta) override;
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
};
