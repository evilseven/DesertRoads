// Copyright 2017 Binary Scroll Interactive

#include "GameOverWidget.h"
#include "TextBlock.h"

UGameOverWidget::UGameOverWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, TotalSecondsUntilRestart(3)
{
}

bool UGameOverWidget::Initialize()
{
	const bool bInitialized = Super::Initialize();
	RemainingSecondsUntilRestart = TotalSecondsUntilRestart;
	return bInitialized;
}

void UGameOverWidget::UpdateRestartLabel(const FText & newText)
{
	if (RestartLabel != nullptr)
	{
		RestartLabel->SetText(newText);
	}
}


