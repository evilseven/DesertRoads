// Copyright 2017 Binary Scroll Interactive

#include "ActorSpawnVolume.h"
#include "DesertRoadsGameStateBase.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Math/RandomStream.h"

AActorSpawnVolume::AActorSpawnVolume()
	: SpawnIntervalMin(0.0f)
	, SpawnIntervalMax(1.0f)
{
}

void AActorSpawnVolume::Disable()
{
	GetWorld()->GetTimerManager().ClearTimer(ActorSpawnTimeHandle);
}

void AActorSpawnVolume::BeginPlay()
{
	Super::BeginPlay();
	ADesertRoadsGameStateBase* const MyGameState = GetWorld()->GetGameState<ADesertRoadsGameStateBase>();
	if (MyGameState != nullptr)
	{
		MyGameState->SetActorSpawner(this);
	}
	RNG.GenerateNewSeed();
	GetWorld()->GetTimerManager().SetTimer(ActorSpawnTimeHandle, this, &AActorSpawnVolume::SpawnNewActor, GetNewSpawnTime(), false);
}

void AActorSpawnVolume::SpawnNewActor()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	GetWorld()->SpawnActor<AActor>(ActorTemplate, GetNewSpawnPosition(), GetActorRotation(), SpawnParams);
	GetWorld()->GetTimerManager().SetTimer(ActorSpawnTimeHandle, this, &AActorSpawnVolume::SpawnNewActor, GetNewSpawnTime(), false);
}

float AActorSpawnVolume::GetNewSpawnTime() const
{
	return RNG.FRandRange(SpawnIntervalMin, SpawnIntervalMax);
}

FVector AActorSpawnVolume::GetNewSpawnPosition() const
{
	FVector Origin;
	FVector BoxExtent;
	GetActorBounds(false, Origin, BoxExtent);
	const float minX = Origin.X - BoxExtent.X;
	const float maxX = Origin.X + BoxExtent.X;
	const float minY = Origin.Y - BoxExtent.Y;
	const float maxY = Origin.Y + BoxExtent.Y;
	const float minZ = Origin.Z - BoxExtent.Z;
	const float maxZ = Origin.Z + BoxExtent.Z;
	return FVector(RNG.FRandRange(minX, maxX), RNG.FRandRange(minY, maxY), RNG.FRandRange(minZ, maxZ));
}
