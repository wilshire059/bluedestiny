#include "W_ItemWheelSlot.h"

void UW_ItemWheelSlot::SetupSlot(const FInventoryItem& Item)
{
	CurrentItem = Item;

	// Icon and quantity would be set from Item data
	// Implementation depends on how FInventoryItem stores icon reference
}

void UW_ItemWheelSlot::UpdateQuantity(int32 Quantity)
{
	if (QuantityText)
	{
		if (Quantity > 1)
		{
			QuantityText->SetText(FText::AsNumber(Quantity));
			QuantityText->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			QuantityText->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}

void UW_ItemWheelSlot::ClearSlot()
{
	CurrentItem = FInventoryItem();

	if (ItemIcon)
	{
		ItemIcon->SetVisibility(ESlateVisibility::Collapsed);
	}

	if (QuantityText)
	{
		QuantityText->SetVisibility(ESlateVisibility::Collapsed);
	}
}
