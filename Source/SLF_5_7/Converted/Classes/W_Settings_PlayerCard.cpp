#include "W_Settings_PlayerCard.h"

void UW_Settings_PlayerCard::NativeConstruct()
{
	Super::NativeConstruct();
}

void UW_Settings_PlayerCard::SetupPlayerCard(FText PlayerName, float PlayTimeSeconds)
{
	if (PlayerNameText)
	{
		PlayerNameText->SetText(PlayerName);
	}

	if (PlayTimeText)
	{
		int32 Hours = FMath::FloorToInt(PlayTimeSeconds / 3600.0f);
		int32 Minutes = FMath::FloorToInt(FMath::Fmod(PlayTimeSeconds, 3600.0f) / 60.0f);
		FText TimeText = FText::Format(NSLOCTEXT("PlayerCard", "PlayTime", "{0}h {1}m"), Hours, Minutes);
		PlayTimeText->SetText(TimeText);
	}
}
