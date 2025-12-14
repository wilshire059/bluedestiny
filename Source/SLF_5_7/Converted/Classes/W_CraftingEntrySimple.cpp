#include "W_CraftingEntrySimple.h"

void UW_CraftingEntrySimple::SetupSimpleEntry(UTexture2D* Icon, FText ItemName, int32 RequiredQuantity, int32 OwnedQuantity)
{
	if (ItemIcon && Icon)
	{
		ItemIcon->SetBrushFromTexture(Icon);
	}

	if (ItemNameText)
	{
		ItemNameText->SetText(ItemName);
	}

	if (RequiredQuantityText)
	{
		RequiredQuantityText->SetText(FText::AsNumber(RequiredQuantity));
	}

	if (OwnedQuantityText)
	{
		OwnedQuantityText->SetText(FText::AsNumber(OwnedQuantity));

		// Color based on whether player has enough
		FSlateColor Color = OwnedQuantity >= RequiredQuantity ? FSlateColor(FLinearColor::White) : FSlateColor(FLinearColor::Red);
		OwnedQuantityText->SetColorAndOpacity(Color);
	}
}
