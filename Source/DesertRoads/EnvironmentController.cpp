// Copyright 2017 Binary Scroll Interactive

#include "EnvironmentController.h"

#include "DesertRoadsGameStateBase.h"
#include "Engine/World.h"
#include "PaperSpriteComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "TimerManager.h"


// Sets default values
AEnvironmentController::AEnvironmentController()
	: StopEnvironmentAnimationsDelay(1.0f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnvironmentController::BeginPlay()
{
	Super::BeginPlay();
	ADesertRoadsGameStateBase* const MyGameState = GetWorld()->GetGameState<ADesertRoadsGameStateBase>();
	if (MyGameState != nullptr)
	{
		MyGameState->SetEnvironmentController(this);
	}
}

// Called every frame
void AEnvironmentController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnvironmentController::StopAnimationsDelayed()
{
	if (StopEnvironmentAnimationsDelay < KINDA_SMALL_NUMBER)
	{
		StopAnimations();
	}
	else
	{
		GetWorld()->GetTimerManager().SetTimer(StopEnvironmentAnimationsHandle, this, &AEnvironmentController::StopAnimations, StopEnvironmentAnimationsDelay, false);
	}
}

void AEnvironmentController::StopAnimations()
{
	for (auto comp : GetComponents())
	{
		UPaperSpriteComponent* spriteComp = Cast<UPaperSpriteComponent>(comp);
		if (spriteComp != nullptr)
		{
			if (spriteComp->ComponentHasTag(FName(TEXT("Black"))))
			{
				spriteComp->SetSpriteColor(FLinearColor::Black);
			}
			else if (spriteComp->ComponentHasTag(FName(TEXT("Hide"))))
			{
				spriteComp->SetSpriteColor(FLinearColor::Transparent);
			}
			else if (spriteComp->ComponentHasTag(FName(TEXT("Blue"))))
			{
				// Not really used, but it looks cool!
				spriteComp->SetSpriteColor(FLinearColor::Blue);
			}
		}
	}
}

