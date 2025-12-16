#include "AC_InventoryManager.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"
#include "Components/AC_StatManager.h"
#include "Components/AC_EquipmentManager.h"
#include "Components/AC_BuffManager.h"
#include "Components/AC_SaveLoadManager.h"
#include "Classes/B_Stat.h"
#include "DataAssets/PDA_Item.h"

UAC_InventoryManager::UAC_InventoryManager()
{
    PrimaryComponentTick.bCanEverTick = false;
    MaxInventorySlots = 20;
    MaxStorageSlots = 100;
    Currency = 0;
}

void UAC_InventoryManager::BeginPlay()
{
    Super::BeginPlay();
}

// ============================================================
// CORE INVENTORY FUNCTIONS
// ============================================================

void UAC_InventoryManager::AddItem(UPDA_Item* Item, int32 Count)
{
    if (!Item || Count <= 0)
    {
        return;
    }

    // Check if item already exists in Items map
    if (int32* ExistingCount = Items.Find(Item))
    {
        *ExistingCount += Count;
    }
    else
    {
        Items.Add(Item, Count);
    }

    // Also update Inventory array for legacy compatibility
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
    OnItemAdded.Broadcast(Item, Count);
}

bool UAC_InventoryManager::AddItemToStorage(UPDA_Item* Item, int32 Count)
{
    if (!Item || Count <= 0)
    {
        return false;
    }

    // Check if storage has room
    if (Storage.Num() >= MaxStorageSlots)
    {
        return false;
    }

    // Check if item already exists in storage
    if (int32* ExistingCount = StoredItems.Find(Item))
    {
        *ExistingCount += Count;
    }
    else
    {
        StoredItems.Add(Item, Count);
    }

    // Update Storage array
    bool bFound = false;
    for (FInventoryItem& StorageItem : Storage)
    {
        if (StorageItem.ItemAsset == Item)
        {
            StorageItem.Amount += Count;
            bFound = true;
            break;
        }
    }

    if (!bFound)
    {
        FInventoryItem NewItem;
        NewItem.ItemAsset = Item;
        NewItem.Amount = Count;
        Storage.Add(NewItem);
    }

    OnStorageUpdated.Broadcast();
    return true;
}

void UAC_InventoryManager::RemoveItem(UPDA_Item* Item, int32 Count)
{
    if (!Item || Count <= 0)
    {
        return;
    }

    // Update Items map
    if (int32* ExistingCount = Items.Find(Item))
    {
        *ExistingCount -= Count;
        if (*ExistingCount <= 0)
        {
            Items.Remove(Item);
        }
    }

    // Update Inventory array
    int32 Index = FindItemIndex(Item);
    if (Index >= 0)
    {
        Inventory[Index].Amount -= Count;
        if (Inventory[Index].Amount <= 0)
        {
            Inventory.RemoveAt(Index);
        }
        OnInventoryUpdated.Broadcast(Item);
        OnItemRemoved.Broadcast(Item, Count);
    }
}

void UAC_InventoryManager::RemoveStoredItem(UPDA_Item* Item, int32 Count)
{
    if (!Item || Count <= 0)
    {
        return;
    }

    // Update StoredItems map
    if (int32* ExistingCount = StoredItems.Find(Item))
    {
        *ExistingCount -= Count;
        if (*ExistingCount <= 0)
        {
            StoredItems.Remove(Item);
        }
    }

    // Update Storage array
    for (int32 i = 0; i < Storage.Num(); i++)
    {
        if (Storage[i].ItemAsset == Item)
        {
            Storage[i].Amount -= Count;
            if (Storage[i].Amount <= 0)
            {
                Storage.RemoveAt(i);
            }
            break;
        }
    }

    OnStorageUpdated.Broadcast();
}

void UAC_InventoryManager::ReplenishItem(UPDA_Item* Item)
{
    if (!Item)
    {
        return;
    }

    // Replenish item to its max stack size
    // This is typically used for consumables at resting points
    if (int32* ExistingCount = Items.Find(Item))
    {
        // Reset to max amount (would come from item data)
        int32 MaxAmount = 10; // Default, should come from item properties
        *ExistingCount = MaxAmount;

        // Update Inventory array
        int32 Index = FindItemIndex(Item);
        if (Index >= 0)
        {
            Inventory[Index].Amount = MaxAmount;
        }

        OnInventoryUpdated.Broadcast(Item);
    }
}

int32 UAC_InventoryManager::GetAmountOfItem(UPDA_Item* Item) const
{
    if (!Item)
    {
        return 0;
    }

    if (const int32* Count = Items.Find(Item))
    {
        return *Count;
    }

    // Fallback to Inventory array
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
    if (!ItemTag.IsValid())
    {
        return 0;
    }

    for (const FInventoryItem& InvItem : Inventory)
    {
        if (InvItem.ItemAsset && InvItem.ItemAsset->ItemInformation.ItemTag == ItemTag)
        {
            return InvItem.Amount;
        }
    }
    return 0;
}

int32 UAC_InventoryManager::GetSlotWithItem(UPDA_Item* Item) const
{
    if (!Item)
    {
        return -1;
    }

    for (int32 i = 0; i < Inventory.Num(); i++)
    {
        if (Inventory[i].ItemAsset == Item)
        {
            return i;
        }
    }
    return -1;
}

int32 UAC_InventoryManager::GetSlotWithItemTag(FGameplayTag ItemTag, E_InventorySlotType SlotType) const
{
    if (!ItemTag.IsValid())
    {
        return -1;
    }

    const TArray<FInventoryItem>& TargetArray = (SlotType == E_InventorySlotType::StorageSlot) ? Storage : Inventory;

    for (int32 i = 0; i < TargetArray.Num(); i++)
    {
        if (TargetArray[i].ItemAsset && TargetArray[i].ItemAsset->ItemInformation.ItemTag == ItemTag)
        {
            return i;
        }
    }
    return -1;
}

UPDA_Item* UAC_InventoryManager::GetItemAtSlot(E_InventorySlotType SlotType, int32 SlotIndex) const
{
    const TArray<FInventoryItem>& TargetArray = (SlotType == E_InventorySlotType::StorageSlot) ? Storage : Inventory;

    if (SlotIndex >= 0 && SlotIndex < TargetArray.Num())
    {
        return TargetArray[SlotIndex].ItemAsset;
    }
    return nullptr;
}

int32 UAC_InventoryManager::GetEmptySlot() const
{
    // Return next available slot index if we have room
    // Original Blueprint used W_InventorySlot widgets to track occupancy
    // For C++, we use array count as proxy for occupied slots
    if (Inventory.Num() < MaxInventorySlots)
    {
        return Inventory.Num();
    }
    return -1;
}

void UAC_InventoryManager::AddNewSlots(int32 Count)
{
    MaxInventorySlots += Count;
}

int32 UAC_InventoryManager::GetTotalInventoryItemsCount() const
{
    int32 Total = 0;
    for (const FInventoryItem& InvItem : Inventory)
    {
        Total += InvItem.Amount;
    }
    return Total;
}

int32 UAC_InventoryManager::GetTotalStorageItemsCount() const
{
    int32 Total = 0;
    for (const FInventoryItem& StorageItem : Storage)
    {
        Total += StorageItem.Amount;
    }
    return Total;
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

// ============================================================
// INITIALIZATION / SAVE LOAD
// ============================================================

void UAC_InventoryManager::InitializeLoadedInventory(const TArray<FInventoryItem>& LoadedInventory)
{
    Inventory = LoadedInventory;

    // Rebuild Items map
    Items.Empty();
    for (const FInventoryItem& InvItem : Inventory)
    {
        if (InvItem.ItemAsset)
        {
            Items.Add(InvItem.ItemAsset, InvItem.Amount);
        }
    }
}

void UAC_InventoryManager::InitializeLoadedStorage(const TArray<FInventoryItem>& LoadedStorage)
{
    Storage = LoadedStorage;

    // Rebuild StoredItems map
    StoredItems.Empty();
    for (const FInventoryItem& StorageItem : Storage)
    {
        if (StorageItem.ItemAsset)
        {
            StoredItems.Add(StorageItem.ItemAsset, StorageItem.Amount);
        }
    }
}

UAC_SaveLoadManager* UAC_InventoryManager::GetSaveLoadComponent() const
{
    AActor* Owner = GetOwner();
    if (Owner)
    {
        return Owner->FindComponentByClass<UAC_SaveLoadManager>();
    }
    return nullptr;
}

void UAC_InventoryManager::GetSaveDataByTag(FGameplayTag Tag)
{
    // Placeholder: would retrieve save data by tag
}

// ============================================================
// CURRENCY
// ============================================================

void UAC_InventoryManager::AdjustCurrency(int32 Delta)
{
    Currency = FMath::Max(0, Currency + Delta);
}

int32 UAC_InventoryManager::GetCurrentCurrency() const
{
    return Currency;
}

// ============================================================
// EQUIPMENT (Facade - Placeholder implementations)
// ============================================================

void UAC_InventoryManager::UnequipItemAtSlot(E_InventorySlotType SlotType, int32 SlotIndex)
{
    // Placeholder: requires AC_EquipmentManager
}

void UAC_InventoryManager::UnequipWeaponAtSlot(E_ActionWeaponSlot WeaponSlot)
{
    // Placeholder: requires AC_EquipmentManager
}

void UAC_InventoryManager::UnequipArmorAtSlot(int32 SlotIndex)
{
    // Placeholder: requires AC_EquipmentManager
}

void UAC_InventoryManager::UnequipTalismanAtSlot(int32 SlotIndex)
{
    // Placeholder: requires AC_EquipmentManager
}

void UAC_InventoryManager::UnequipToolAtSlot(int32 SlotIndex)
{
    // Placeholder: requires AC_EquipmentManager
}

void UAC_InventoryManager::OnWeaponUnequip(E_ActionWeaponSlot WeaponSlot)
{
    // Placeholder: requires AC_EquipmentManager
}

void UAC_InventoryManager::RefreshActiveGuardSequence()
{
    // Placeholder: requires AC_EquipmentManager
}

void UAC_InventoryManager::ResetHeadpiece()
{
    // Placeholder: requires AC_EquipmentManager
}

void UAC_InventoryManager::ResetArmor()
{
    // Placeholder: requires AC_EquipmentManager
}

void UAC_InventoryManager::ResetGloves()
{
    // Placeholder: requires AC_EquipmentManager
}

void UAC_InventoryManager::ResetGreaves()
{
    // Placeholder: requires AC_EquipmentManager
}

bool UAC_InventoryManager::AreBothWeaponSlotsActive() const
{
    // Placeholder: requires AC_EquipmentManager
    return false;
}

E_ActionWeaponSlot UAC_InventoryManager::GetActiveWeaponSlot() const
{
    // Placeholder: requires AC_EquipmentManager
    return E_ActionWeaponSlot::RightHand;
}

bool UAC_InventoryManager::IsItemEquipped(UPDA_Item* Item) const
{
    // Placeholder: requires AC_EquipmentManager
    return false;
}

// ============================================================
// STATS (Facade)
// ============================================================

UB_Stat* UAC_InventoryManager::GetStat(FGameplayTag StatTag) const
{
    APawn* Pawn = GetPawnFromController();
    if (Pawn)
    {
        if (UAC_StatManager* StatMgr = Pawn->FindComponentByClass<UAC_StatManager>())
        {
            return StatMgr->GetStat(StatTag);
        }
    }
    return nullptr;
}

void UAC_InventoryManager::AdjustStat(FGameplayTag StatTag, float Delta)
{
    // Placeholder: requires AC_StatManager::AdjustStat
}

void UAC_InventoryManager::AdjustValue(UB_Stat* Stat, float Delta)
{
    if (Stat)
    {
        Stat->ModifyStat(Delta);
    }
}

void UAC_InventoryManager::ApplyStatChanges(const TArray<FStatInfo>& StatChanges)
{
    // Placeholder: requires AC_StatManager::ApplyStatChanges
}

// ============================================================
// BUFFS (Facade)
// ============================================================

void UAC_InventoryManager::TryRemoveBuffs(const FGameplayTagContainer& BuffTags)
{
    // Placeholder: requires AC_BuffManager::TryRemoveBuffs
}

UAC_BuffManager* UAC_InventoryManager::GetBuffManager() const
{
    APawn* Pawn = GetPawnFromController();
    if (Pawn)
    {
        return Pawn->FindComponentByClass<UAC_BuffManager>();
    }
    return nullptr;
}

// ============================================================
// MOVEMENT & STATE
// ============================================================

void UAC_InventoryManager::SetMovementMode(E_MovementType MovementType)
{
    // Placeholder: requires character interface
}

void UAC_InventoryManager::UpdateOverlayStates(E_OverlayState NewState)
{
    // Placeholder: requires character interface
}

// ============================================================
// UI
// ============================================================

UUserWidget* UAC_InventoryManager::GetInventoryWidget() const
{
    // Placeholder: implementation depends on UI system
    return nullptr;
}

UUserWidget* UAC_InventoryManager::GetPlayerHUD() const
{
    // Placeholder: implementation depends on UI system
    return nullptr;
}

// ============================================================
// INPUT BUFFER
// ============================================================

void UAC_InventoryManager::QueueAction(FGameplayTag ActionTag)
{
    // Placeholder: action buffer system
}

void UAC_InventoryManager::ConsumeInputBuffer()
{
    // Placeholder: action buffer system
}

// ============================================================
// UTILITY
// ============================================================

APawn* UAC_InventoryManager::GetPawnFromController() const
{
    AActor* Owner = GetOwner();
    if (!Owner)
    {
        return nullptr;
    }

    // If owner is a pawn, return it
    if (APawn* Pawn = Cast<APawn>(Owner))
    {
        return Pawn;
    }

    // If owner is a controller, get its pawn
    if (APlayerController* PC = Cast<APlayerController>(Owner))
    {
        return PC->GetPawn();
    }

    return nullptr;
}
