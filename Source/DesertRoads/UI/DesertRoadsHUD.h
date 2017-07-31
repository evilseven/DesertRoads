// Copyright 2017 Binary Scroll Interactive

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "DesertRoadsHUD.generated.h"

/**
 * 
 */
UCLASS()
class DESERTROADS_API ADesertRoadsHUD : public AHUD
{
	GENERATED_BODY()
	
private:

	UPROPERTY(Category = "HUD", EditAnywhere)
	TSubclassOf<class UVehicleHUD> HUDTemplate;

	UPROPERTY(Category = "Game Over", EditAnywhere)
	TSubclassOf<class UGameOverWidget> GameOverTemplate;

	UPROPERTY(Category = "Game Over", EditDefaultsOnly)
	float OpenGameOverDelay;

	UPROPERTY(Category = "Victory", EditAnywhere)
	TSubclassOf<class UUserWidget> VictoryTemplate;

	UPROPERTY(Transient)
	class UVehicleHUD* HUDInstance;

	UPROPERTY(Transient)
	class UGameOverWidget* GameOverInstance;

	UPROPERTY(Transient)
	class UUserWidget* VictoryInstance;

	UPROPERTY(Transient)
	FTimerHandle OpenGameOverHandle;

	UPROPERTY(Transient)
	FTimerHandle GameOverUpdateHandle;

	UPROPERTY(Transient)
	FTimerHandle TimeUpdateHandle;

public:

	ADesertRoadsHUD();

	void UpdateTime();
	void OpenVictoryScreen();
	void OpenGameOverScreen();
	void OpenGameOverScreenDelayed();
	void UpdateGameOverScreen();
	virtual void BeginPlay() override;
	
	
};
