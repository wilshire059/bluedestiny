#include "DataAssets/PDA_Item.h"

void UPDA_Item::UnlockCrafting()
{
    if (ItemInformation.CraftingDetails.bCanBeCrafted)
    {
        bCraftingUnlocked = true;
        OnCraftingUnlocked.Broadcast();
    }
}

TMap<FGameplayTag, int32> UPDA_Item::GetRequiredCraftingItems() const
{
    return ItemInformation.CraftingDetails.RequiredItems;
}
