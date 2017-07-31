// Copyright 2017 Binary Scroll Interactive

#include "VehicleHUD.h"
#include "VehicleCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Components/ProgressBar.h"
#include "TextBlock.h"

UVehicleHUD::UVehicleHUD(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, TotalTime(60)
{
}

bool UVehicleHUD::Initialize()
{
	const bool bInitialized = Super::Initialize();
	if (FuelProgressBar != nullptr)
	{
		VehicleCharacter = Cast<AVehicleCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));	
	}
	RemainingTime = TotalTime;
	return bInitialized;
}

void UVehicleHUD::UpdateTimeLabel(const FText & newText)
{
	if (TimeLabel != nullptr)
	{
		TimeLabel->SetText(newText);
	}
}

void UVehicleHUD::DecreaseRemainingTime()
{
	RemainingTime--;
	if (RemainingTime == 0)
	{
		VehicleCharacter->TimeUp();
	}
}
