// Copyright 2017 Binary Scroll Interactive

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "VehicleHUD.generated.h"

/**
 * 
 */
UCLASS()
class DESERTROADS_API UVehicleHUD : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(BlueprintReadOnly)
	class AVehicleCharacter* VehicleCharacter;

private:

	UPROPERTY(meta=(BindWidget="FuelProgressBar"))
	class UProgressBar* FuelProgressBar;

	UPROPERTY(Category = "Time", EditDefaultsOnly)
	int TotalTime;

	UPROPERTY(meta = (BindWidget = "TimeLabel"))
	class UTextBlock* TimeLabel;

	int RemainingTime;
	
public:

	int GetTotalTime() const { return TotalTime; }
	int GetRemainingTime() const { return RemainingTime; }
	void DecreaseRemainingTime();

	UVehicleHUD(const FObjectInitializer& ObjectInitializer);
	virtual bool Initialize() override;
	void UpdateTimeLabel(const FText & newText);
	
};
