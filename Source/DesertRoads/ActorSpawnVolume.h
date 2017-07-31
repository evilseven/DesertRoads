// Copyright 2017 Binary Scroll Interactive

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Volume.h"
#include "ActorSpawnVolume.generated.h"

/**
 * 
 */
UCLASS()
class DESERTROADS_API AActorSpawnVolume : public AVolume
{
	GENERATED_BODY()
	
private:

	UPROPERTY(Category = "Spawning", EditAnywhere)
	TSubclassOf<AActor> ActorTemplate;

	UPROPERTY(Category = "Spawning", meta = (ClampMin = 0), EditAnywhere)
	float SpawnIntervalMin;

	UPROPERTY(Category = "Spawning", meta = (ClampMin = 0), EditAnywhere)
	float SpawnIntervalMax;

	UPROPERTY(Transient)
	FTimerHandle ActorSpawnTimeHandle;

	UPROPERTY(Transient)
	struct FRandomStream RNG;

public:

	AActorSpawnVolume();
	void Disable();

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	void SpawnNewActor();

	FVector GetNewSpawnPosition() const;
	float GetNewSpawnTime() const;
	
};
