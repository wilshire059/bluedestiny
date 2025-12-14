#include "W_InventorySlot.h"
#include "DataAssets/PDA_Item.h"

void UW_InventorySlot::OccupySlot(UPDA_Item* Item, int32 Count)
{
    AssignedItem = Item;
    bIsOccupied = true;
    ItemAmountValue = Count;

    if (ItemIcon && Item && !Item->ItemInformation.IconSmall.IsNull())
    {
        ItemIcon->SetBrushFromSoftTexture(Item->ItemInformation.IconSmall);
        ItemIcon->SetVisibility(ESlateVisibility::Visible);
    }

    if (ItemAmount)
    {
        ItemAmount->SetText(FText::AsNumber(Count));
        // Logic to hide amount if 1 or not stackable could be added
        ItemAmount->SetVisibility(ESlateVisibility::Visible);
    }

    OnOccupiedSlot.Broadcast(Item, Count);
}

void UW_InventorySlot::ClearSlot()
{
    AssignedItem = nullptr;
    bIsOccupied = false;
    ItemAmountValue = 0;

    if (ItemIcon)
    {
        ItemIcon->SetVisibility(ESlateVisibility::Hidden);
    }
    if (ItemAmount)
    {
        ItemAmount->SetVisibility(ESlateVisibility::Hidden);
    }

    OnClearSlot.Broadcast();
}

void UW_InventorySlot::ChangeAmount(int32 NewCount)
{
    ItemAmountValue = NewCount;
    if (ItemAmount)
    {
        ItemAmount->SetText(FText::AsNumber(NewCount));
    }
    OnChangeAmount.Broadcast(NewCount);
}
