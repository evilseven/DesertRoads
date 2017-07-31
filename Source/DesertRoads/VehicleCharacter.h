// Copyright 2017 Binary Scroll Interactive

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "VehicleCharacter.generated.h"

/**
 * 
 */
UCLASS()
class DESERTROADS_API AVehicleCharacter : public APaperCharacter
{
	GENERATED_BODY()
	
private:

	// TODO: Those are only for UI and should probably be at a better place I cannot find at the moment
	UPROPERTY(Category = "Visualization", EditDefaultsOnly)
	FLinearColor EmptyFuelColorization;

	UPROPERTY(Category = "Visualization", EditDefaultsOnly)
	FLinearColor FullFuelColorization;

protected:

	UPROPERTY(Transient, BlueprintReadOnly)
	float CurrentFuelPercentage;

	UPROPERTY(Transient, BlueprintReadOnly)
	FLinearColor CurrentFuelColorization;
	
private:

	UPROPERTY(Category = "Movement", EditDefaultsOnly)
	float Speed;

	UPROPERTY(Category = "Fuel", EditDefaultsOnly)
	float MaxFuel;

	UPROPERTY(Category = "Fuel", EditDefaultsOnly)
	float FuelConsumeRate;

	UPROPERTY(Category = "Audio", EditDefaultsOnly)
	class USoundCue* TimeUpSound;

	UPROPERTY(Category = "Audio", EditDefaultsOnly)
	class USoundCue* OutOfFuelSound;

	UPROPERTY(Category = "Audio", EditDefaultsOnly)
	class UAudioComponent* VehicleAudioComponent;

	float CurrentFuel;
	bool bGameOver;

private:

	UPROPERTY(Category = "Camera", EditDefaultsOnly)
	class UCameraComponent* Camera;
	
public:

	AVehicleCharacter();

	virtual void BeginPlay() override;
	virtual void Tick(float Delta) override;

	void UpdateFuel(float FuelDelta);
	void TimeUp();

protected:

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

private:

	void MoveUp(float Value);
	void InitFuel();
	void UpdateFuelVisualization();
	void HandleOutOfFuel();
	void Quit();
};
