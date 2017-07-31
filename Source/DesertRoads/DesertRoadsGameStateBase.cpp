// Copyright 2017 Binary Scroll Interactive

#include "DesertRoadsGameStateBase.h"

#include "ActorSpawnVolume.h"
#include "UI/DesertRoadsHUD.h"
#include "EnvironmentController.h"
#include "Engine/World.h"

ADesertRoadsGameStateBase::ADesertRoadsGameStateBase()
{
}

void ADesertRoadsGameStateBase::SetEnvironmentController(AEnvironmentController * environmentController)
{
	this->EnvironmentController = environmentController;
}

void ADesertRoadsGameStateBase::SetActorSpawner(AActorSpawnVolume * actorSpawner)
{
	this->ActorSpawner = actorSpawner;
}

void ADesertRoadsGameStateBase::HandleGameOver(bool bVictory)
{
	ActorSpawner->Disable();
	if (!bVictory)
	{
		EnvironmentController->StopAnimationsDelayed();
	}
	if (GetWorld() != nullptr)
	{
		ADesertRoadsHUD* const hud = Cast<ADesertRoadsHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
		if (hud != nullptr)
		{
			if (bVictory)
			{
				hud->OpenVictoryScreen();
			}
			else
			{
				hud->OpenGameOverScreenDelayed();
			}
		}
	}
}
