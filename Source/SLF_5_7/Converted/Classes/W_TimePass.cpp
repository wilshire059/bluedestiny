#include "W_TimePass.h"

void UW_TimePass::StartTimePass(float TargetTime, float Duration)
{
	bIsTransitioning = true;
	TransitionProgress = 0.0f;
	TransitionDuration = Duration;
	SetVisibility(ESlateVisibility::Visible);
}

void UW_TimePass::UpdateTimeDisplay(float CurrentTime)
{
	if (TimeText)
	{
		int32 Hours = FMath::FloorToInt(CurrentTime);
		int32 Minutes = FMath::FloorToInt((CurrentTime - Hours) * 60.0f);
		FText TimeFormatted = FText::Format(NSLOCTEXT("TimePass", "Time", "{0}:{1}"),
			FText::AsNumber(Hours),
			FText::FromString(FString::Printf(TEXT("%02d"), Minutes)));
		TimeText->SetText(TimeFormatted);
	}
}

void UW_TimePass::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (bIsTransitioning)
	{
		TransitionProgress += InDeltaTime;

		if (TransitionProgress >= TransitionDuration)
		{
			bIsTransitioning = false;
			OnTimePassComplete.Broadcast();
			SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}
