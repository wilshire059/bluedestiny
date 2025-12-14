#include "W_Status_LevelCurrencyBlock.h"

void UW_Status_LevelCurrencyBlock::NativeConstruct()
{
	Super::NativeConstruct();
	RefreshDisplay();
}

void UW_Status_LevelCurrencyBlock::RefreshDisplay()
{
	// Refresh from stat manager if available
	if (UAC_StatManager* LocalStatManager = GetStatComponent())
	{
		// Implementation would query level and currency from stat manager
	}
}

void UW_Status_LevelCurrencyBlock::UpdateLevelDisplay(int32 Level)
{
	if (LevelText)
	{
		LevelText->SetText(FText::AsNumber(Level));
	}
}

void UW_Status_LevelCurrencyBlock::UpdateCurrencyDisplay(int64 Currency)
{
	if (CurrencyText)
	{
		CurrencyText->SetText(FText::AsNumber(Currency));
	}
}
