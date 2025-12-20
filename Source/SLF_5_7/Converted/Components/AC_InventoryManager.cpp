#include "AC_InventoryManager.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/HUD.h"
#include "Components/AC_StatManager.h"
#include "Components/AC_EquipmentManager.h"
#include "Components/AC_BuffManager.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AC_SaveLoadManager.h"
#include "Classes/B_Stat.h"
#include "DataAssets/PDA_Item.h"
#include "Enums/E_ValueType.h"

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
    // Broadcast save request - the save/load manager handles actual persistence
    OnSaveRequested.Broadcast(Tag);
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
// EQUIPMENT (Facade to AC_EquipmentManager)
// ============================================================

void UAC_InventoryManager::UnequipItemAtSlot(E_InventorySlotType SlotType, int32 SlotIndex)
{
    APawn* Pawn = GetPawnFromController();
    if (Pawn)
    {
        if (UAC_EquipmentManager* EquipMgr = Pawn->FindComponentByClass<UAC_EquipmentManager>())
        {
            // The actual slot tag mapping depends on slot type configuration
        }
    }
}

void UAC_InventoryManager::UnequipWeaponAtSlot(E_ActionWeaponSlot WeaponSlot)
{
    APawn* Pawn = GetPawnFromController();
    if (Pawn)
    {
        if (UAC_EquipmentManager* EquipMgr = Pawn->FindComponentByClass<UAC_EquipmentManager>())
        {
            EquipMgr->UnequipWeaponAtSlot(WeaponSlot);
        }
    }
}

void UAC_InventoryManager::UnequipArmorAtSlot(int32 SlotIndex)
{
    APawn* Pawn = GetPawnFromController();
    if (Pawn)
    {
        if (UAC_EquipmentManager* EquipMgr = Pawn->FindComponentByClass<UAC_EquipmentManager>())
        {
            EquipMgr->UnequipArmorAtSlot(SlotIndex);
        }
    }
}

void UAC_InventoryManager::UnequipTalismanAtSlot(int32 SlotIndex)
{
    APawn* Pawn = GetPawnFromController();
    if (Pawn)
    {
        if (UAC_EquipmentManager* EquipMgr = Pawn->FindComponentByClass<UAC_EquipmentManager>())
        {
            EquipMgr->UnequipTalismanAtSlot(SlotIndex);
        }
    }
}

void UAC_InventoryManager::UnequipToolAtSlot(int32 SlotIndex)
{
    APawn* Pawn = GetPawnFromController();
    if (Pawn)
    {
        if (UAC_EquipmentManager* EquipMgr = Pawn->FindComponentByClass<UAC_EquipmentManager>())
        {
            EquipMgr->UnequipToolAtSlot(SlotIndex);
        }
    }
}

void UAC_InventoryManager::OnWeaponUnequip(E_ActionWeaponSlot WeaponSlot)
{
    APawn* Pawn = GetPawnFromController();
    if (Pawn)
    {
        if (UAC_EquipmentManager* EquipMgr = Pawn->FindComponentByClass<UAC_EquipmentManager>())
        {
            EquipMgr->OnWeaponUnequip(WeaponSlot);
        }
    }
}

void UAC_InventoryManager::RefreshActiveGuardSequence()
{
    APawn* Pawn = GetPawnFromController();
    if (Pawn)
    {
        if (UAC_EquipmentManager* EquipMgr = Pawn->FindComponentByClass<UAC_EquipmentManager>())
        {
            EquipMgr->RefreshActiveGuardSequence();
        }
    }
}

void UAC_InventoryManager::ResetHeadpiece()
{
    APawn* Pawn = GetPawnFromController();
    if (Pawn)
    {
        if (UAC_EquipmentManager* EquipMgr = Pawn->FindComponentByClass<UAC_EquipmentManager>())
        {
            EquipMgr->ResetHeadpiece();
        }
    }
}

void UAC_InventoryManager::ResetArmor()
{
    APawn* Pawn = GetPawnFromController();
    if (Pawn)
    {
        if (UAC_EquipmentManager* EquipMgr = Pawn->FindComponentByClass<UAC_EquipmentManager>())
        {
            EquipMgr->ResetArmor();
        }
    }
}

void UAC_InventoryManager::ResetGloves()
{
    APawn* Pawn = GetPawnFromController();
    if (Pawn)
    {
        if (UAC_EquipmentManager* EquipMgr = Pawn->FindComponentByClass<UAC_EquipmentManager>())
        {
            EquipMgr->ResetGloves();
        }
    }
}

void UAC_InventoryManager::ResetGreaves()
{
    APawn* Pawn = GetPawnFromController();
    if (Pawn)
    {
        if (UAC_EquipmentManager* EquipMgr = Pawn->FindComponentByClass<UAC_EquipmentManager>())
        {
            EquipMgr->ResetGreaves();
        }
    }
}

bool UAC_InventoryManager::AreBothWeaponSlotsActive() const
{
    APawn* Pawn = GetPawnFromController();
    if (Pawn)
    {
        if (UAC_EquipmentManager* EquipMgr = Pawn->FindComponentByClass<UAC_EquipmentManager>())
        {
            return EquipMgr->AreBothWeaponSlotsActive();
        }
    }
    return false;
}

E_ActionWeaponSlot UAC_InventoryManager::GetActiveWeaponSlot() const
{
    APawn* Pawn = GetPawnFromController();
    if (Pawn)
    {
        if (UAC_EquipmentManager* EquipMgr = Pawn->FindComponentByClass<UAC_EquipmentManager>())
        {
            return EquipMgr->GetActiveWeaponSlot();
        }
    }
    return E_ActionWeaponSlot::Right;
}

bool UAC_InventoryManager::IsItemEquipped(UPDA_Item* Item) const
{
    APawn* Pawn = GetPawnFromController();
    if (Pawn)
    {
        if (UAC_EquipmentManager* EquipMgr = Pawn->FindComponentByClass<UAC_EquipmentManager>())
        {
            return EquipMgr->AllEquippedItems.Contains(Item);
        }
    }
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
    APawn* Pawn = GetPawnFromController();
    if (Pawn)
    {
        if (UAC_StatManager* StatMgr = Pawn->FindComponentByClass<UAC_StatManager>())
        {
            StatMgr->ModifyStat(StatTag, Delta, E_ValueType::Flat);
        }
    }
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
    APawn* Pawn = GetPawnFromController();
    if (Pawn)
    {
        if (UAC_StatManager* StatMgr = Pawn->FindComponentByClass<UAC_StatManager>())
        {
            for (const FStatInfo& StatChange : StatChanges)
            {
                // Use Tag property and default to Flat value type
                StatMgr->ModifyStat(StatChange.Tag, StatChange.Value, E_ValueType::Flat);
            }
        }
    }
}

// ============================================================
// BUFFS (Facade)
// ============================================================

void UAC_InventoryManager::TryRemoveBuffs(const FGameplayTagContainer& BuffTags)
{
    if (UAC_BuffManager* BuffMgr = GetBuffManager())
    {
        BuffMgr->TryRemoveBuffs(BuffTags);
    }
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
    APawn* Pawn = GetPawnFromController();
    if (Pawn)
    {
        if (UAC_EquipmentManager* EquipMgr = Pawn->FindComponentByClass<UAC_EquipmentManager>())
        {
            EquipMgr->SetMovementMode(MovementType);
        }
    }
}

void UAC_InventoryManager::UpdateOverlayStates(E_OverlayState NewState)
{
    APawn* Pawn = GetPawnFromController();
    if (Pawn)
    {
        if (UAC_EquipmentManager* EquipMgr = Pawn->FindComponentByClass<UAC_EquipmentManager>())
        {
            EquipMgr->UpdateOverlayStates(NewState);
        }
    }
}

// ============================================================
// UI
// ============================================================

UUserWidget* UAC_InventoryManager::GetInventoryWidget() const
{
    // Inventory widget is typically cached or accessed via HUD
    // Returns nullptr - actual implementation handled in Blueprint HUD
    return nullptr;
}

UUserWidget* UAC_InventoryManager::GetPlayerHUD() const
{
    if (APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0))
    {
        if (AHUD* HUD = PC->GetHUD())
        {
            // HUD widget access depends on specific HUD implementation
        }
    }
    return nullptr;
}

// ============================================================
// INPUT BUFFER
// ============================================================

void UAC_InventoryManager::QueueAction(FGameplayTag ActionTag)
{
    // Add action to input buffer queue
    InputBuffer.AddUnique(ActionTag);
}

void UAC_InventoryManager::ConsumeInputBuffer()
{
    // Process and clear the input buffer
    for (const FGameplayTag& ActionTag : InputBuffer)
    {
        OnActionQueued.Broadcast(ActionTag);
    }
    InputBuffer.Empty();
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
