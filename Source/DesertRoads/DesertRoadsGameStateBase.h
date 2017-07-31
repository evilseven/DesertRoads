// Copyright 2017 Binary Scroll Interactive

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "DesertRoadsGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class DESERTROADS_API ADesertRoadsGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
	
private:

	UPROPERTY(Transient)
	class AEnvironmentController* EnvironmentController;

	UPROPERTY(Transient)
	class AActorSpawnVolume* ActorSpawner;

public:

	ADesertRoadsGameStateBase();
	void SetEnvironmentController(class AEnvironmentController* environmentController);
	void SetActorSpawner(class AActorSpawnVolume* actorSpawner);
	void HandleGameOver(bool bVictory = false);
	
	
};
