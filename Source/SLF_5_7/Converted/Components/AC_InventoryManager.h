#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "Structs/FInventoryItem.h"
#include "Structs/FSLFItemInfo.h"
#include "Structs/FStatInfo.h"
#include "Enums/E_InventorySlotType.h"
#include "Enums/E_ActionWeaponSlot.h"
#include "Enums/E_MovementType.h"
#include "Enums/E_OverlayState.h"
#include "AC_InventoryManager.generated.h"

class UPDA_Item;
class UB_Stat;
class UAC_BuffManager;
class UAC_SaveLoadManager;
class UUserWidget;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInventoryUpdated, const UPDA_Item*, Item);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnItemAdded, UPDA_Item*, Item, int32, Amount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnItemRemoved, UPDA_Item*, Item, int32, Amount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStorageUpdated);

UCLASS(ClassGroup = (Custom), Blueprintable, meta = (BlueprintSpawnableComponent))
class SLF_5_7_API UAC_InventoryManager : public UActorComponent
{
    GENERATED_BODY()

public:
    UAC_InventoryManager();

    // ============================================================
    // PROPERTIES
    // ============================================================

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
    TArray<FInventoryItem> Inventory;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
    TArray<FInventoryItem> Storage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
    TMap<TObjectPtr<UPDA_Item>, int32> Items;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
    TMap<TObjectPtr<UPDA_Item>, int32> StoredItems;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
    int32 MaxInventorySlots;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
    int32 MaxStorageSlots;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
    int32 Currency;

    // ============================================================
    // DELEGATES
    // ============================================================

    UPROPERTY(BlueprintAssignable, Category = "Inventory")
    FOnInventoryUpdated OnInventoryUpdated;

    UPROPERTY(BlueprintAssignable, Category = "Inventory")
    FOnItemAdded OnItemAdded;

    UPROPERTY(BlueprintAssignable, Category = "Inventory")
    FOnItemRemoved OnItemRemoved;

    UPROPERTY(BlueprintAssignable, Category = "Inventory")
    FOnStorageUpdated OnStorageUpdated;

    // ============================================================
    // CORE INVENTORY FUNCTIONS
    // ============================================================

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    void AddItem(UPDA_Item* Item, int32 Count);

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    bool AddItemToStorage(UPDA_Item* Item, int32 Count);

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    void RemoveItem(UPDA_Item* Item, int32 Count);

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    void RemoveStoredItem(UPDA_Item* Item, int32 Count);

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    void ReplenishItem(UPDA_Item* Item);

    UFUNCTION(BlueprintPure, Category = "Inventory")
    int32 GetAmountOfItem(UPDA_Item* Item) const;

    UFUNCTION(BlueprintPure, Category = "Inventory")
    int32 GetAmountOfItemByTag(FGameplayTag ItemTag) const;

    UFUNCTION(BlueprintPure, Category = "Inventory")
    int32 GetSlotWithItem(UPDA_Item* Item) const;

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    int32 GetSlotWithItemTag(FGameplayTag ItemTag, E_InventorySlotType SlotType) const;

    UFUNCTION(BlueprintPure, Category = "Inventory")
    UPDA_Item* GetItemAtSlot(E_InventorySlotType SlotType, int32 SlotIndex) const;

    UFUNCTION(BlueprintPure, Category = "Inventory")
    int32 GetEmptySlot() const;

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    void AddNewSlots(int32 Count);

    UFUNCTION(BlueprintPure, Category = "Inventory")
    int32 GetTotalInventoryItemsCount() const;

    UFUNCTION(BlueprintPure, Category = "Inventory")
    int32 GetTotalStorageItemsCount() const;

    // ============================================================
    // INITIALIZATION / SAVE LOAD
    // ============================================================

    UFUNCTION(BlueprintCallable, Category = "Inventory|Save")
    void InitializeLoadedInventory(const TArray<FInventoryItem>& LoadedInventory);

    UFUNCTION(BlueprintCallable, Category = "Inventory|Save")
    void InitializeLoadedStorage(const TArray<FInventoryItem>& LoadedStorage);

    UFUNCTION(BlueprintPure, Category = "Inventory|Save")
    UAC_SaveLoadManager* GetSaveLoadComponent() const;

    UFUNCTION(BlueprintCallable, Category = "Inventory|Save")
    void GetSaveDataByTag(FGameplayTag Tag);

    // ============================================================
    // CURRENCY
    // ============================================================

    UFUNCTION(BlueprintCallable, Category = "Inventory|Currency")
    void AdjustCurrency(int32 Delta);

    UFUNCTION(BlueprintPure, Category = "Inventory|Currency")
    int32 GetCurrentCurrency() const;

    // ============================================================
    // EQUIPMENT (Facade to AC_EquipmentManager)
    // ============================================================

    UFUNCTION(BlueprintCallable, Category = "Inventory|Equipment")
    void UnequipItemAtSlot(E_InventorySlotType SlotType, int32 SlotIndex);

    UFUNCTION(BlueprintCallable, Category = "Inventory|Equipment")
    void UnequipWeaponAtSlot(E_ActionWeaponSlot WeaponSlot);

    UFUNCTION(BlueprintCallable, Category = "Inventory|Equipment")
    void UnequipArmorAtSlot(int32 SlotIndex);

    UFUNCTION(BlueprintCallable, Category = "Inventory|Equipment")
    void UnequipTalismanAtSlot(int32 SlotIndex);

    UFUNCTION(BlueprintCallable, Category = "Inventory|Equipment")
    void UnequipToolAtSlot(int32 SlotIndex);

    UFUNCTION(BlueprintCallable, Category = "Inventory|Equipment")
    void OnWeaponUnequip(E_ActionWeaponSlot WeaponSlot);

    UFUNCTION(BlueprintCallable, Category = "Inventory|Equipment")
    void RefreshActiveGuardSequence();

    UFUNCTION(BlueprintCallable, Category = "Inventory|Equipment")
    void ResetHeadpiece();

    UFUNCTION(BlueprintCallable, Category = "Inventory|Equipment")
    void ResetArmor();

    UFUNCTION(BlueprintCallable, Category = "Inventory|Equipment")
    void ResetGloves();

    UFUNCTION(BlueprintCallable, Category = "Inventory|Equipment")
    void ResetGreaves();

    UFUNCTION(BlueprintPure, Category = "Inventory|Equipment")
    bool AreBothWeaponSlotsActive() const;

    UFUNCTION(BlueprintPure, Category = "Inventory|Equipment")
    E_ActionWeaponSlot GetActiveWeaponSlot() const;

    UFUNCTION(BlueprintPure, Category = "Inventory|Equipment")
    bool IsItemEquipped(UPDA_Item* Item) const;

    // ============================================================
    // STATS (Facade to AC_StatManager)
    // ============================================================

    UFUNCTION(BlueprintPure, Category = "Inventory|Stats")
    UB_Stat* GetStat(FGameplayTag StatTag) const;

    UFUNCTION(BlueprintCallable, Category = "Inventory|Stats")
    void AdjustStat(FGameplayTag StatTag, float Delta);

    UFUNCTION(BlueprintCallable, Category = "Inventory|Stats")
    void AdjustValue(UB_Stat* Stat, float Delta);

    UFUNCTION(BlueprintCallable, Category = "Inventory|Stats")
    void ApplyStatChanges(const TArray<FStatInfo>& StatChanges);

    // ============================================================
    // BUFFS (Facade to AC_BuffManager)
    // ============================================================

    UFUNCTION(BlueprintCallable, Category = "Inventory|Buffs")
    void TryRemoveBuffs(const FGameplayTagContainer& BuffTags);

    UFUNCTION(BlueprintPure, Category = "Inventory|Buffs")
    UAC_BuffManager* GetBuffManager() const;

    // ============================================================
    // MOVEMENT & STATE
    // ============================================================

    UFUNCTION(BlueprintCallable, Category = "Inventory|Movement")
    void SetMovementMode(E_MovementType MovementType);

    UFUNCTION(BlueprintCallable, Category = "Inventory|Movement")
    void UpdateOverlayStates(E_OverlayState NewState);

    // ============================================================
    // UI
    // ============================================================

    UFUNCTION(BlueprintPure, Category = "Inventory|UI")
    UUserWidget* GetInventoryWidget() const;

    UFUNCTION(BlueprintPure, Category = "Inventory|UI")
    UUserWidget* GetPlayerHUD() const;

    // ============================================================
    // INPUT BUFFER
    // ============================================================

    UFUNCTION(BlueprintCallable, Category = "Inventory|Input")
    void QueueAction(FGameplayTag ActionTag);

    UFUNCTION(BlueprintCallable, Category = "Inventory|Input")
    void ConsumeInputBuffer();

    // ============================================================
    // UTILITY
    // ============================================================

    UFUNCTION(BlueprintPure, Category = "Inventory|Utility")
    APawn* GetPawnFromController() const;

    // Helper to find item index
    int32 FindItemIndex(UPDA_Item* Item) const;

protected:
    virtual void BeginPlay() override;
};
