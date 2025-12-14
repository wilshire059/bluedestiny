#include "W_CurrencyEntry.h"

void UW_CurrencyEntry::SetupCurrencyEntry(UTexture2D* Icon, int64 Amount)
{
	if (CurrencyIcon && Icon)
	{
		CurrencyIcon->SetBrushFromTexture(Icon);
	}

	UpdateAmount(Amount);
}

void UW_CurrencyEntry::UpdateAmount(int64 NewAmount)
{
	if (CurrencyAmountText)
	{
		CurrencyAmountText->SetText(FText::AsNumber(NewAmount));
	}
}
