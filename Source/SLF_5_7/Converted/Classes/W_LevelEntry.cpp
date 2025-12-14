#include "W_LevelEntry.h"

void UW_LevelEntry::SetupLevelEntry(int32 Level)
{
	if (LevelValueText)
	{
		LevelValueText->SetText(FText::AsNumber(Level));
	}
}
