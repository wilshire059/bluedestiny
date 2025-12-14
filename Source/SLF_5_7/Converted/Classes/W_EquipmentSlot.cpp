#include "W_EquipmentSlot.h"
#include "DataAssets/PDA_Item.h"

void UW_EquipmentSlot::NativePreConstruct()
{
    Super::NativePreConstruct();

    if (ItemBackgroundIcon && !BackgroundIcon.IsNull())
    {
        ItemBackgroundIcon->SetBrushFromSoftTexture(BackgroundIcon);
    }
}

void UW_EquipmentSlot::OccupyEquipmentSlot(UPDA_Item* Item)
{
    AssignedItem = Item;
    bIsOccupied = true;
    
    if (ItemIcon && Item && !Item->ItemInformation.IconSmall.IsNull())
    {
        ItemIcon->SetBrushFromSoftTexture(Item->ItemInformation.IconSmall);
        ItemIcon->SetVisibility(ESlateVisibility::Visible);
    }

    OnOccupiedEquipmentSlot.Broadcast(Item);
}

void UW_EquipmentSlot::ClearEquipmentSlot()
{
    AssignedItem = nullptr;
    bIsOccupied = false;

    if (ItemIcon)
    {
        ItemIcon->SetVisibility(ESlateVisibility::Hidden);
    }

    OnClearEquipmentSlot.Broadcast();
}
