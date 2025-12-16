#include "AC_EquipmentManager.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "Components/AC_StatManager.h"
#include "Components/AC_BuffManager.h"
#include "Components/AC_SaveLoadManager.h"
#include "Classes/B_Stat.h"
#include "DataAssets/PDA_Item.h"

UAC_EquipmentManager::UAC_EquipmentManager()
{
    PrimaryComponentTick.bCanEverTick = false;
    RightHandOverlayState = E_OverlayState::Unarmed;
    LeftHandOverlayState = E_OverlayState::Unarmed;
    bIsAsyncWeaponBusy = false;
    bIsCrouched = false;
    WeaponAbilitySlot = E_WeaponAbilityHandle::RightHand;
}

void UAC_EquipmentManager::BeginPlay()
{
    Super::BeginPlay();
}

// ============================================================
// WEAPON EQUIP/UNEQUIP
// ============================================================

void UAC_EquipmentManager::EquipWeaponToSlot(UPDA_Item* Item, FGameplayTag SlotTag)
{
    if (!Item || !SlotTag.IsValid())
    {
        return;
    }

    // Add to current equipment
    CurrentEquipment.Add(SlotTag, Item);
    AllEquippedItems.AddUnique(Item);

    // Determine if right hand
    bool bRightHand = RightHandSlots.HasTag(SlotTag);

    // Trigger equip event
    OnWeaponEquip(Item, bRightHand);
    OnEquipmentChanged.Broadcast(SlotTag, Item);
}

void UAC_EquipmentManager::UnequipWeaponAtSlot(E_ActionWeaponSlot WeaponSlot)
{
    // Find the appropriate slot tag based on weapon slot
    FGameplayTag SlotTag;

    // Placeholder: Would map E_ActionWeaponSlot to actual gameplay tags
    if (CurrentEquipment.Remove(SlotTag))
    {
        OnWeaponUnequip(WeaponSlot);
        OnEquipmentChanged.Broadcast(SlotTag, nullptr);
    }
}

void UAC_EquipmentManager::OnWeaponEquip(UPDA_Item* Item, bool bRightHand)
{
    if (!Item)
    {
        return;
    }

    // Update overlay state based on equipped weapon
    // This would read from Item->EquipmentInfo.WeaponOverlay

    // Grant tags from equipment
    // GrantedTags.AppendTags(Item->EquipmentInfo.GrantedTags);

    // Broadcast delegate
    OnWeaponEquipDelegate.Broadcast(Item, bRightHand);

    // Refresh guard sequence for blocking
    RefreshActiveGuardSequence();
}

void UAC_EquipmentManager::OnWeaponUnequip(E_ActionWeaponSlot WeaponSlot)
{
    // Remove granted tags, reset overlay state, etc.
    OnWeaponUnequipDelegate.Broadcast(WeaponSlot);
    RefreshActiveGuardSequence();
}

void UAC_EquipmentManager::WieldItemAtSlot(FGameplayTag SlotTag)
{
    if (!SlotTag.IsValid())
    {
        return;
    }

    // Set as active slot
    ActiveSlot = SlotTag;

    // Placeholder: Would trigger animations and visual changes
}

void UAC_EquipmentManager::AsyncSpawnAndEquipWeapon(FGameplayTag SlotTag, UPDA_Item* Item)
{
    if (!Item || bIsAsyncWeaponBusy)
    {
        return;
    }

    bIsAsyncWeaponBusy = true;

    // Placeholder: Would async load the item class and spawn it
    // Using soft class reference loading
    // On completion, attach to appropriate socket and mark as equipped

    bIsAsyncWeaponBusy = false;
}

// ============================================================
// ARMOR EQUIP/UNEQUIP
// ============================================================

void UAC_EquipmentManager::EquipArmorToSlot(UPDA_Item* Item, FGameplayTag SlotTag)
{
    if (!Item || !SlotTag.IsValid())
    {
        return;
    }

    CurrentEquipment.Add(SlotTag, Item);
    AllEquippedItems.AddUnique(Item);
    OnEquipmentChanged.Broadcast(SlotTag, Item);

    // Apply stat changes from armor
    // ApplyStatChanges(Item->EquipmentInfo.Stats);
}

void UAC_EquipmentManager::UnequipArmorAtSlot(int32 SlotIndex)
{
    // Placeholder: Would find armor slot tag by index and unequip
}

void UAC_EquipmentManager::ChangeHeadpiece(USkeletalMesh* NewMesh)
{
    // Placeholder: Would set the headpiece mesh on character
}

void UAC_EquipmentManager::ChangeArmor(USkeletalMesh* NewMesh)
{
    // Placeholder: Would set the armor mesh on character
}

void UAC_EquipmentManager::ChangeGloves(USkeletalMesh* NewMesh)
{
    // Placeholder: Would set the gloves mesh on character
}

void UAC_EquipmentManager::ChangeGreaves(USkeletalMesh* NewMesh)
{
    // Placeholder: Would set the greaves mesh on character
}

void UAC_EquipmentManager::ResetHeadpiece()
{
    // Placeholder: Would reset to default headpiece mesh
}

void UAC_EquipmentManager::ResetArmor()
{
    // Placeholder: Would reset to default armor mesh
}

void UAC_EquipmentManager::ResetGloves()
{
    // Placeholder: Would reset to default gloves mesh
}

void UAC_EquipmentManager::ResetGreaves()
{
    // Placeholder: Would reset to default greaves mesh
}

// ============================================================
// TALISMAN/TOOL EQUIP/UNEQUIP
// ============================================================

void UAC_EquipmentManager::EquipTalismanToSlot(UPDA_Item* Item, FGameplayTag SlotTag)
{
    if (!Item || !SlotTag.IsValid())
    {
        return;
    }

    CurrentEquipment.Add(SlotTag, Item);
    AllEquippedItems.AddUnique(Item);
    OnEquipmentChanged.Broadcast(SlotTag, Item);

    // Talismans typically grant buffs
    // TryGrantBuffs(Item->EquipmentInfo.GrantedTags);
}

void UAC_EquipmentManager::UnequipTalismanAtSlot(int32 SlotIndex)
{
    // Placeholder: Would find talisman slot by index and unequip
}

void UAC_EquipmentManager::EquipToolToSlot(UPDA_Item* Item, FGameplayTag SlotTag)
{
    if (!Item || !SlotTag.IsValid())
    {
        return;
    }

    CurrentEquipment.Add(SlotTag, Item);
    AllEquippedItems.AddUnique(Item);
    OnEquipmentChanged.Broadcast(SlotTag, Item);
}

void UAC_EquipmentManager::UnequipToolAtSlot(int32 SlotIndex)
{
    // Placeholder: Would find tool slot by index and unequip
}

// ============================================================
// GENERIC EQUIP/UNEQUIP
// ============================================================

void UAC_EquipmentManager::UnequipItemAtSlot(FGameplayTag SlotTag, int32 SlotIndex)
{
    if (!SlotTag.IsValid())
    {
        return;
    }

    if (TObjectPtr<UPDA_Item>* FoundItem = CurrentEquipment.Find(SlotTag))
    {
        UPDA_Item* Item = *FoundItem;
        AllEquippedItems.Remove(Item);
        CurrentEquipment.Remove(SlotTag);
        OnEquipmentChanged.Broadcast(SlotTag, nullptr);
    }
}

UPDA_Item* UAC_EquipmentManager::GetItemAtSlot(FGameplayTag SlotTag) const
{
    if (const TObjectPtr<UPDA_Item>* FoundItem = CurrentEquipment.Find(SlotTag))
    {
        return *FoundItem;
    }
    return nullptr;
}

bool UAC_EquipmentManager::IsSlotOccupied(FGameplayTag SlotTag) const
{
    return CurrentEquipment.Contains(SlotTag);
}

// ============================================================
// WEAPON STATE
// ============================================================

E_ActionWeaponSlot UAC_EquipmentManager::GetActiveWeaponSlot() const
{
    // Determine active slot based on current state
    if (WeaponAbilitySlot == E_WeaponAbilityHandle::RightHand)
    {
        return E_ActionWeaponSlot::RightHand;
    }
    return E_ActionWeaponSlot::LeftHand;
}

bool UAC_EquipmentManager::AreBothWeaponSlotsActive() const
{
    // Check if both hands have equipped weapons
    bool bHasRightHand = false;
    bool bHasLeftHand = false;

    for (const auto& Pair : CurrentEquipment)
    {
        if (RightHandSlots.HasTag(Pair.Key))
        {
            bHasRightHand = true;
        }
        if (LeftHandSlots.HasTag(Pair.Key))
        {
            bHasLeftHand = true;
        }
    }

    return bHasRightHand && bHasLeftHand;
}

bool UAC_EquipmentManager::GetTwoHandStance() const
{
    // Check if wielding a two-handed weapon
    // Placeholder: Would check equipped weapon's properties
    return false;
}

void UAC_EquipmentManager::RefreshActiveGuardSequence()
{
    // Update the active block sequence based on equipped shield/weapon
    // Would set Guard_R, Guard_L, or ActiveBlockSequence based on equipment
}

int32 UAC_EquipmentManager::GetActiveWheelSlotForWeapon(bool bRightHand) const
{
    // Placeholder: Would query the item wheel widget for active slot
    return 0;
}

int32 UAC_EquipmentManager::GetActiveWheelSlotForTool() const
{
    // Placeholder: Would query the tool wheel widget for active slot
    return 0;
}

// ============================================================
// OVERLAY & MOVEMENT
// ============================================================

void UAC_EquipmentManager::UpdateOverlayStates(E_OverlayState NewState)
{
    // Placeholder: Would update character overlay/animation state
}

void UAC_EquipmentManager::SetMovementMode(E_MovementType MovementType)
{
    // Placeholder: Would set character movement mode
}

void UAC_EquipmentManager::ReinitializeMovementWithWeight(float Weight)
{
    // Placeholder: Would recalculate movement speed based on equipment weight
}

bool UAC_EquipmentManager::GetIsCrouched() const
{
    return bIsCrouched;
}

// ============================================================
// STATS (Facade to AC_StatManager)
// ============================================================

UB_Stat* UAC_EquipmentManager::GetStat(FGameplayTag StatTag) const
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

void UAC_EquipmentManager::AdjustStat(FGameplayTag StatTag, float Delta)
{
    // Placeholder: Would call AC_StatManager::AdjustStat
}

void UAC_EquipmentManager::AdjustValue(UB_Stat* Stat, float Delta)
{
    if (Stat)
    {
        Stat->ModifyStat(Delta);
    }
}

void UAC_EquipmentManager::ApplyStatChanges(const TArray<FStatInfo>& StatChanges)
{
    // Placeholder: Would apply each stat change to the stat manager
}

// ============================================================
// BUFFS (Facade to AC_BuffManager)
// ============================================================

void UAC_EquipmentManager::TryGrantBuffs(const FGameplayTagContainer& BuffTags)
{
    // Placeholder: Would call AC_BuffManager::TryGrantBuffs
}

void UAC_EquipmentManager::TryRemoveBuffs(const FGameplayTagContainer& BuffTags)
{
    // Placeholder: Would call AC_BuffManager::TryRemoveBuffs
}

UAC_BuffManager* UAC_EquipmentManager::GetBuffManager() const
{
    APawn* Pawn = GetPawnFromController();
    if (Pawn)
    {
        return Pawn->FindComponentByClass<UAC_BuffManager>();
    }
    return nullptr;
}

// ============================================================
// SAVE/LOAD
// ============================================================

void UAC_EquipmentManager::ConvertToEquipmentItemsSaveInfoStructs(TArray<FEquipmentItemsSaveInfo>& OutSaveInfo)
{
    OutSaveInfo.Empty();

    int32 Index = 0;
    for (const auto& Pair : CurrentEquipment)
    {
        FEquipmentItemsSaveInfo SaveInfo;
        SaveInfo.SlotTag = Pair.Key;
        SaveInfo.EquippedItem = Pair.Value;
        SaveInfo.SlotIndex = Index++;
        OutSaveInfo.Add(SaveInfo);
    }
}

void UAC_EquipmentManager::InitLoadedItems(const TArray<FEquipmentItemsSaveInfo>& LoadedItems)
{
    Cached_LoadedEquipment = LoadedItems;

    // Re-equip loaded items
    for (const FEquipmentItemsSaveInfo& SaveInfo : LoadedItems)
    {
        if (UPDA_Item* Item = SaveInfo.EquippedItem.LoadSynchronous())
        {
            CurrentEquipment.Add(SaveInfo.SlotTag, Item);
            AllEquippedItems.AddUnique(Item);
        }
    }

    RefreshActiveGuardSequence();
}

UAC_SaveLoadManager* UAC_EquipmentManager::GetSaveLoadComponent() const
{
    AActor* Owner = GetOwner();
    if (Owner)
    {
        return Owner->FindComponentByClass<UAC_SaveLoadManager>();
    }
    return nullptr;
}

void UAC_EquipmentManager::GetSaveDataByTag(FGameplayTag Tag)
{
    // Placeholder: Would retrieve save data by tag from save system
}

// ============================================================
// HELPERS
// ============================================================

APawn* UAC_EquipmentManager::GetPawnFromController() const
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

bool UAC_EquipmentManager::GetMeshInitialized() const
{
    // Placeholder: Would check if character mesh is initialized
    return true;
}

UUserWidget* UAC_EquipmentManager::GetPlayerHUD() const
{
    // Placeholder: Would return player HUD widget
    return nullptr;
}

TSubclassOf<AActor> UAC_EquipmentManager::GetSelectedClass() const
{
    // Placeholder: Would return selected character class
    return nullptr;
}

bool UAC_EquipmentManager::IsValidArray(const TArray<UPDA_Item*>& Array) const
{
    return Array.Num() > 0;
}

void UAC_EquipmentManager::SwitchOnSlot(FGameplayTag SlotTag)
{
    // Placeholder: Would switch behavior based on slot type
}

void UAC_EquipmentManager::FastForEachLoop(const TArray<UPDA_Item*>& Items)
{
    // Placeholder: Would iterate items for batch operations
}
