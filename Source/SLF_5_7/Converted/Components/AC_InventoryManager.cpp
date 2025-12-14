#include "Components/AC_InventoryManager.h"

UAC_InventoryManager::UAC_InventoryManager()
{
    PrimaryComponentTick.bCanEverTick = false;
}

int32 UAC_InventoryManager::GetAmountOfItem(UPDA_Item* Item) const
{
    if (!Item) return 0;
    
    for (const FInventoryItem& InvItem : Inventory)
    {
        if (InvItem.ItemAsset == Item)
        {
            return InvItem.Amount;
        }
    }
    return 0;
}

int32 UAC_InventoryManager::GetAmountOfItemByTag(FGameplayTag ItemTag) const
{
    if (!ItemTag.IsValid()) return 0;

    for (const FInventoryItem& InvItem : Inventory)
    {
        if (InvItem.ItemAsset && InvItem.ItemAsset->ItemInformation.ItemTag == ItemTag)
        {
            return InvItem.Amount;
        }
    }
    return 0;
}

void UAC_InventoryManager::AddItem(UPDA_Item* Item, int32 Count)
{
    if (!Item || Count <= 0) return;

    int32 Index = FindItemIndex(Item);
    if (Index >= 0)
    {
        Inventory[Index].Amount += Count;
    }
    else
    {
        FInventoryItem NewItem;
        NewItem.ItemAsset = Item;
        NewItem.Amount = Count;
        Inventory.Add(NewItem);
    }
    
    OnInventoryUpdated.Broadcast(Item);
}

void UAC_InventoryManager::RemoveItem(UPDA_Item* Item, int32 Count)
{
    if (!Item || Count <= 0) return;

    int32 Index = FindItemIndex(Item);
    if (Index >= 0)
    {
        Inventory[Index].Amount -= Count;
        if (Inventory[Index].Amount <= 0)
        {
            Inventory.RemoveAt(Index);
        }
        OnInventoryUpdated.Broadcast(Item);
    }
}

int32 UAC_InventoryManager::FindItemIndex(UPDA_Item* Item) const
{
    for (int32 i = 0; i < Inventory.Num(); i++)
    {
        if (Inventory[i].ItemAsset == Item)
        {
            return i;
        }
    }
    return -1;
}

void UAC_InventoryManager::AdjustCurrency(int32 Delta)
{
    Currency += Delta;
    if (Currency < 0) Currency = 0;
    // Broadcast?
}

void UAC_InventoryManager::GetSlotWithItemTag(FGameplayTag ItemTag, E_InventorySlotType SlotType)
{
    // Implementation ambiguous from Blueprint analysis. 
    // However, we now have GetAmountOfItemByTag which serves the logic purpose for B_Door.
    // This function will remain a stub or print a log to avoid logic errors until further usage analysis.
    // Ideally it would return a Slot Index or Item, but signature is void.
}
