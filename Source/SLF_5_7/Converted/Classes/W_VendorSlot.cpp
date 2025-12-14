#include "W_VendorSlot.h"

void UW_VendorSlot::NativeConstruct()
{
	Super::NativeConstruct();

	if (SlotButton)
	{
		SlotButton->OnClicked.AddDynamic(this, &UW_VendorSlot::HandleSlotClicked);
	}
}

void UW_VendorSlot::SetupSlot(int32 InSlotIndex, const FInventoryItem& Item, int64 Price)
{
	SlotIndex = InSlotIndex;
	ItemData = Item;

	// Item icon and name would be set from Item data asset
	// Implementation depends on FInventoryItem structure

	if (PriceText)
	{
		PriceText->SetText(FText::AsNumber(Price));
	}

	if (QuantityText)
	{
		if (Item.Amount > 1)
		{
			QuantityText->SetText(FText::AsNumber(Item.Amount));
			QuantityText->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			QuantityText->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}

void UW_VendorSlot::HandleSlotClicked()
{
	OnVendorSlotSelected.Broadcast(SlotIndex);
}

void UW_VendorSlot::SetSelected(bool bSelected)
{
	// Visual feedback for selection - implemented in Blueprint
}
