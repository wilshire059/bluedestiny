#include "W_LevelUpCost.h"

void UW_LevelUpCost::UpdateCostDisplay(int64 Cost, int64 CurrentCurrency)
{
	if (CostText)
	{
		CostText->SetText(FText::AsNumber(Cost));

		// Red if can't afford, white if can
		FSlateColor Color = CurrentCurrency >= Cost ? FSlateColor(FLinearColor::White) : FSlateColor(FLinearColor::Red);
		CostText->SetColorAndOpacity(Color);
	}

	if (CurrentCurrencyText)
	{
		CurrentCurrencyText->SetText(FText::AsNumber(CurrentCurrency));
	}
}
