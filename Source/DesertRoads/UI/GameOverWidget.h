// Copyright 2017 Binary Scroll Interactive

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameOverWidget.generated.h"

/**
 * 
 */
UCLASS()
class DESERTROADS_API UGameOverWidget : public UUserWidget
{
	GENERATED_BODY()
	
private:

	UPROPERTY(Category = "Game Over", EditDefaultsOnly)
	int TotalSecondsUntilRestart;

	int RemainingSecondsUntilRestart;

	UPROPERTY(meta = (BindWidget = "RestartLabel"))
	class UTextBlock* RestartLabel;

public:

	virtual bool Initialize() override;

	int GetTotalSecondsUntilRestart() const { return TotalSecondsUntilRestart; }
	int GetRemainingSecondsUntilRestart() const { return RemainingSecondsUntilRestart; }
	void DecreaseSecondsUntilRestart() { RemainingSecondsUntilRestart--; }
	void UpdateRestartLabel(const FText& newText);
	
	UGameOverWidget(const FObjectInitializer& ObjectInitializer);
	
};
