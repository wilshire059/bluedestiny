#include "W_LevelCurrencyBlock_LevelUp.h"

void UW_LevelCurrencyBlock_LevelUp::NativeConstruct()
{
	Super::NativeConstruct();
	RefreshDisplay();
}

void UW_LevelCurrencyBlock_LevelUp::RefreshDisplay()
{
	// Initial refresh from stat manager
}

void UW_LevelCurrencyBlock_LevelUp::UpdateDisplay(int32 CurrentLevel, int32 NewLevel, int64 CurrentCurrency, int64 RequiredCurrency)
{
	if (CurrentLevelText)
	{
		CurrentLevelText->SetText(FText::AsNumber(CurrentLevel));
	}

	if (NewLevelText)
	{
		NewLevelText->SetText(FText::AsNumber(NewLevel));
	}

	if (CurrentCurrencyText)
	{
		CurrentCurrencyText->SetText(FText::AsNumber(CurrentCurrency));
	}

	if (RequiredCurrencyText)
	{
		RequiredCurrencyText->SetText(FText::AsNumber(RequiredCurrency));

		// Change color based on affordability
		FSlateColor Color = CurrentCurrency >= RequiredCurrency ? FSlateColor(FLinearColor::White) : FSlateColor(FLinearColor::Red);
		RequiredCurrencyText->SetColorAndOpacity(Color);
	}
}
