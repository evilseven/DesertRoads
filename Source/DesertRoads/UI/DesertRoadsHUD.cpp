// Copyright 2017 Binary Scroll Interactive

#include "DesertRoadsHUD.h"
#include "../DesertRoadsGameStateBase.h"
#include "Blueprint/UserWidget.h"
#include "GameOverWidget.h"
#include "Engine/World.h"
#include "Internationalization/Internationalization.h"
#include "TimerManager.h"
#include "VehicleHUD.h"

#define LOCTEXT_NAMESPACE "Desert Roads UI"

ADesertRoadsHUD::ADesertRoadsHUD()
	: OpenGameOverDelay(1.0f)
{
}

void ADesertRoadsHUD::BeginPlay()
{
	Super::BeginPlay();
	if (HUDTemplate != nullptr)
	{
		// Create the widget and store it.
		HUDInstance = CreateWidget<UVehicleHUD>(GetOwningPlayerController(), HUDTemplate);
		if (HUDInstance != nullptr)
		{
			//let add it to the view port
			HUDInstance->AddToViewport();
			GetWorld()->GetTimerManager().SetTimer(TimeUpdateHandle, this, &ADesertRoadsHUD::UpdateTime, 1.0f, true, 0.0f);
		}
	}
}

void ADesertRoadsHUD::OpenVictoryScreen()
{
	if (HUDInstance != nullptr)
	{
		//let add it to the view port
		HUDInstance->RemoveFromViewport();
	}
	if (VictoryTemplate != nullptr)
	{
		// Create the widget and store it.
		VictoryInstance = CreateWidget<UUserWidget>(GetOwningPlayerController(), VictoryTemplate);
		if (VictoryInstance != nullptr)
		{
			//let add it to the view port
			VictoryInstance->AddToViewport();
		}
	}
}

void ADesertRoadsHUD::OpenGameOverScreenDelayed()
{
	if (OpenGameOverDelay < KINDA_SMALL_NUMBER)
	{
		OpenGameOverScreen();
	}
	else
	{
		GetWorld()->GetTimerManager().SetTimer(OpenGameOverHandle, this, &ADesertRoadsHUD::OpenGameOverScreen, OpenGameOverDelay, false);
	}
}

void ADesertRoadsHUD::OpenGameOverScreen()
{
	GetWorld()->GetTimerManager().ClearTimer(TimeUpdateHandle);
	if (HUDInstance != nullptr)
	{
		//let add it to the view port
		HUDInstance->RemoveFromViewport();
	}
	if (GameOverTemplate != nullptr)
	{
		// Create the widget and store it.
		GameOverInstance = Cast<UGameOverWidget>(CreateWidget<UUserWidget>(GetOwningPlayerController(), GameOverTemplate));
		if (GameOverInstance != nullptr)
		{
			//let add it to the view port
			GameOverInstance->AddToViewport();
			const int secondsUntilRestart = GameOverInstance->GetTotalSecondsUntilRestart();
			if (secondsUntilRestart > 0)
			{
				GetWorld()->GetTimerManager().SetTimer(GameOverUpdateHandle, this, &ADesertRoadsHUD::UpdateGameOverScreen, 1.0f, true, 0.0f);
			}
			
		}
	}
}

void ADesertRoadsHUD::UpdateTime()
{
	const int remainingTime = HUDInstance->GetRemainingTime();
	const FText timeText = FText::Format(LOCTEXT("TimeText", "Time: {0} seconds"), FText::AsNumber(remainingTime));
	HUDInstance->UpdateTimeLabel(timeText);
	HUDInstance->DecreaseRemainingTime();

	if (remainingTime == 0 && GetWorld() != nullptr)
	{
		GetWorld()->GetTimerManager().ClearTimer(TimeUpdateHandle);
		ADesertRoadsGameStateBase* const MyGameState = GetWorld()->GetGameState<ADesertRoadsGameStateBase>();
		if (MyGameState != nullptr)
		{
			MyGameState->HandleGameOver(true);
		}
	}
}

void ADesertRoadsHUD::UpdateGameOverScreen()
{
	const int secondsUntilRestart = GameOverInstance->GetRemainingSecondsUntilRestart();
	const FText restartText = FText::Format(LOCTEXT("RestartText", "{0} seconds until restart!"), FText::AsNumber(secondsUntilRestart));
	GameOverInstance->UpdateRestartLabel(restartText);
	GameOverInstance->DecreaseSecondsUntilRestart();

	if (secondsUntilRestart == 0 && GetWorld() != nullptr)
	{
		GetWorld()->GetFirstPlayerController()->RestartLevel();
	}
}

#undef LOCTEXT_NAMESPACE