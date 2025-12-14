#include "W_SkipCinematic.h"

void UW_SkipCinematic::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (MessageText)
	{
		MessageText->SetText(SkipMessage);
	}
}

void UW_SkipCinematic::StartHolding()
{
	bIsHolding = true;
	CurrentHoldTime = 0.0f;
}

void UW_SkipCinematic::StopHolding()
{
	bIsHolding = false;
	CurrentHoldTime = 0.0f;

	if (SkipProgress)
	{
		SkipProgress->SetPercent(0.0f);
	}
}

void UW_SkipCinematic::UpdateProgress(float DeltaTime)
{
	if (!bIsHolding)
	{
		return;
	}

	CurrentHoldTime += DeltaTime;
	float Progress = FMath::Clamp(CurrentHoldTime / HoldDuration, 0.0f, 1.0f);

	if (SkipProgress)
	{
		SkipProgress->SetPercent(Progress);
	}

	if (CurrentHoldTime >= HoldDuration)
	{
		OnSkipCinematic.Broadcast();
		StopHolding();
	}
}
