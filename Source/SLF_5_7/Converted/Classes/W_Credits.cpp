#include "W_Credits.h"

void UW_Credits::NativeConstruct()
{
	Super::NativeConstruct();
}

void UW_Credits::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (bIsScrolling && CreditsContainer)
	{
		float CurrentOffset = CreditsContainer->GetScrollOffset();
		float MaxOffset = CreditsContainer->GetScrollOffsetOfEnd();

		if (CurrentOffset < MaxOffset)
		{
			CreditsContainer->SetScrollOffset(CurrentOffset + ScrollSpeed * InDeltaTime);
		}
		else
		{
			bIsScrolling = false;
			OnCreditsFinished.Broadcast();
		}
	}
}

void UW_Credits::StartCredits()
{
	bIsScrolling = true;
	if (CreditsContainer)
	{
		CreditsContainer->SetScrollOffset(0.0f);
	}
}

void UW_Credits::SkipCredits()
{
	bIsScrolling = false;
	OnCreditsFinished.Broadcast();
}

void UW_Credits::SetupCredits(const TArray<FCreditsEntry>& Entries)
{
	OnSetupCredits(Entries);
}
