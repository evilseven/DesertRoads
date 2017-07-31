// Copyright 2017 Binary Scroll Interactive

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnvironmentController.generated.h"

UCLASS()
class DESERTROADS_API AEnvironmentController : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(Category = "Game Over", EditDefaultsOnly)
	float StopEnvironmentAnimationsDelay;

private:
	UPROPERTY(Transient)
	FTimerHandle StopEnvironmentAnimationsHandle;
	
public:
	// Sets default values for this actor's properties
	AEnvironmentController();

	void StopAnimations();
	void StopAnimationsDelayed();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
