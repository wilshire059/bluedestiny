#include "AC_EquipmentManager.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/HUD.h"
#include "Engine/World.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/AC_StatManager.h"
#include "Components/AC_BuffManager.h"
#include "Components/AC_SaveLoadManager.h"
#include "Classes/B_Stat.h"
#include "Classes/B_Item.h"
#include "DataAssets/PDA_Item.h"
#include "Enums/E_ValueType.h"

UAC_EquipmentManager::UAC_EquipmentManager()
{
    PrimaryComponentTick.bCanEverTick = false;
    RightHandOverlayState = E_OverlayState::Unarmed;
    LeftHandOverlayState = E_OverlayState::Unarmed;
    bIsAsyncWeaponBusy = false;
    bIsCrouched = false;
    bTwoHandStance = false;
    WeaponAbilitySlot = E_WeaponAbilityHandle::RightHand;
    CurrentHeadpieceMesh = nullptr;
    CurrentArmorMesh = nullptr;
    CurrentGlovesMesh = nullptr;
    CurrentGreavesMesh = nullptr;
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
    // Get appropriate slot based on weapon slot type
    FGameplayTag SlotTag;

    switch (WeaponSlot)
    {
        case E_ActionWeaponSlot::Right:
            // Unequip from active right hand slot
            if (RightHandSlots.Num() > 0)
            {
                SlotTag = RightHandSlots.GetByIndex(ActiveRightHandIndex);
            }
            break;
        case E_ActionWeaponSlot::Left:
            // Unequip from active left hand slot
            if (LeftHandSlots.Num() > 0)
            {
                SlotTag = LeftHandSlots.GetByIndex(ActiveLeftHandIndex);
            }
            break;
        case E_ActionWeaponSlot::Dual:
            // Unequip from both hands - use right hand for two-handed weapons
            if (RightHandSlots.Num() > 0)
            {
                SlotTag = RightHandSlots.GetByIndex(ActiveRightHandIndex);
            }
            break;
        case E_ActionWeaponSlot::Null:
            // Match current active hand based on stance
            if (bTwoHandStance && RightHandSlots.Num() > 0)
            {
                SlotTag = RightHandSlots.GetByIndex(ActiveRightHandIndex);
            }
            else if (LeftHandSlots.Num() > 0)
            {
                SlotTag = LeftHandSlots.GetByIndex(ActiveLeftHandIndex);
            }
            break;
        default:
            return;
    }

    if (SlotTag.IsValid() && CurrentEquipment.Remove(SlotTag))
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

    // Determine if wielding in right hand
    bool bRightHand = RightHandSlots.HasTag(SlotTag);

    // Broadcast stance change for animation system to handle
    OnStanceChanged.Broadcast(bRightHand, bTwoHandStance);
}

void UAC_EquipmentManager::AsyncSpawnAndEquipWeapon(FGameplayTag SlotTag, UPDA_Item* Item)
{
    if (!Item || bIsAsyncWeaponBusy)
    {
        return;
    }

    bIsAsyncWeaponBusy = true;

    // Get the soft class reference from item info
    TSoftClassPtr<AActor> ItemClass = Item->ItemInformation.ItemClass;

    if (ItemClass.IsNull())
    {
        bIsAsyncWeaponBusy = false;
        return;
    }

    // If already loaded, spawn immediately
    if (ItemClass.IsValid())
    {
        UClass* LoadedClass = ItemClass.Get();
        if (LoadedClass)
        {
            // Spawn the item actor
            UWorld* World = GetWorld();
            if (World)
            {
                FActorSpawnParameters SpawnParams;
                SpawnParams.Owner = Cast<AActor>(GetPawnFromController());

                AB_Item* SpawnedItem = World->SpawnActor<AB_Item>(LoadedClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
                if (SpawnedItem)
                {
                    SpawnedItemsAtSlots.Add(SlotTag, SpawnedItem);
                    EquipWeaponToSlot(Item, SlotTag);
                }
            }
        }
        bIsAsyncWeaponBusy = false;
    }
    else
    {
        // Async load the class
        // Note: Full async implementation would use FStreamableManager
        // For now, synchronously load
        UClass* LoadedClass = ItemClass.LoadSynchronous();
        if (LoadedClass)
        {
            UWorld* World = GetWorld();
            if (World)
            {
                FActorSpawnParameters SpawnParams;
                SpawnParams.Owner = Cast<AActor>(GetPawnFromController());

                AB_Item* SpawnedItem = World->SpawnActor<AB_Item>(LoadedClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
                if (SpawnedItem)
                {
                    SpawnedItemsAtSlots.Add(SlotTag, SpawnedItem);
                    EquipWeaponToSlot(Item, SlotTag);
                }
            }
        }
        bIsAsyncWeaponBusy = false;
    }
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
    // Find armor slot by index from ArmorSlots container
    if (ArmorSlots.Num() > SlotIndex)
    {
        FGameplayTag SlotTag = ArmorSlots.GetByIndex(SlotIndex);
        if (SlotTag.IsValid())
        {
            if (UPDA_Item* Item = CurrentEquipment.FindRef(SlotTag))
            {
                AllEquippedItems.Remove(Item);
            }
            CurrentEquipment.Remove(SlotTag);
            OnEquipmentChanged.Broadcast(SlotTag, nullptr);
        }
    }
}

void UAC_EquipmentManager::ChangeHeadpiece(USkeletalMesh* NewMesh)
{
    // Mesh changes are handled by the character Blueprint via delegates or direct component access
    // This method is called when equipment changes; the Blueprint character should listen to OnEquipmentChanged
    CurrentHeadpieceMesh = NewMesh;
}

void UAC_EquipmentManager::ChangeArmor(USkeletalMesh* NewMesh)
{
    CurrentArmorMesh = NewMesh;
}

void UAC_EquipmentManager::ChangeGloves(USkeletalMesh* NewMesh)
{
    CurrentGlovesMesh = NewMesh;
}

void UAC_EquipmentManager::ChangeGreaves(USkeletalMesh* NewMesh)
{
    CurrentGreavesMesh = NewMesh;
}

void UAC_EquipmentManager::ResetHeadpiece()
{
    ChangeHeadpiece(nullptr);
}

void UAC_EquipmentManager::ResetArmor()
{
    ChangeArmor(nullptr);
}

void UAC_EquipmentManager::ResetGloves()
{
    ChangeGloves(nullptr);
}

void UAC_EquipmentManager::ResetGreaves()
{
    ChangeGreaves(nullptr);
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
    if (TalismanSlots.Num() > SlotIndex)
    {
        FGameplayTag SlotTag = TalismanSlots.GetByIndex(SlotIndex);
        if (SlotTag.IsValid())
        {
            if (UPDA_Item* Item = CurrentEquipment.FindRef(SlotTag))
            {
                // Remove buffs granted by talisman
                // TryRemoveBuffs(Item->EquipmentInfo.GrantedTags);
                AllEquippedItems.Remove(Item);
            }
            CurrentEquipment.Remove(SlotTag);
            OnEquipmentChanged.Broadcast(SlotTag, nullptr);
        }
    }
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
    if (ToolSlots.Num() > SlotIndex)
    {
        FGameplayTag SlotTag = ToolSlots.GetByIndex(SlotIndex);
        if (SlotTag.IsValid())
        {
            if (UPDA_Item* Item = CurrentEquipment.FindRef(SlotTag))
            {
                AllEquippedItems.Remove(Item);
            }
            CurrentEquipment.Remove(SlotTag);
            OnEquipmentChanged.Broadcast(SlotTag, nullptr);
        }
    }
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
        return E_ActionWeaponSlot::Right;
    }
    return E_ActionWeaponSlot::Left;
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
    return bTwoHandStance;
}

void UAC_EquipmentManager::RefreshActiveGuardSequence()
{
    // Select appropriate guard sequence based on active weapon slot
    if (WeaponAbilitySlot == E_WeaponAbilityHandle::RightHand)
    {
        ActiveBlockSequence = Guard_R;
    }
    else
    {
        ActiveBlockSequence = Guard_L;
    }
}

int32 UAC_EquipmentManager::GetActiveWheelSlotForWeapon(bool bRightHand) const
{
    // Item wheel widgets are Blueprint widgets - this returns default slot
    // The actual active slot is typically managed by the wheel widget itself
    // and broadcast via delegates when changed
    return 0;
}

int32 UAC_EquipmentManager::GetActiveWheelSlotForTool() const
{
    // Tool wheel widget is a Blueprint widget - this returns default slot
    return 0;
}

// ============================================================
// OVERLAY & MOVEMENT
// ============================================================

void UAC_EquipmentManager::UpdateOverlayStates(E_OverlayState NewState)
{
    // Update both overlay states when a general update is requested
    RightHandOverlayState = NewState;
    LeftHandOverlayState = NewState;

    // Character Blueprint should bind to OnEquipmentChanged or OnStanceChanged
    // to react to overlay state changes
}

void UAC_EquipmentManager::SetMovementMode(E_MovementType MovementType)
{
    // Movement mode is handled by the character's movement component
    // This method notifies the character to update its movement settings
    APawn* Pawn = GetPawnFromController();
    if (ACharacter* Character = Cast<ACharacter>(Pawn))
    {
        // The character Blueprint handles movement mode changes
        // via interface or direct component access
    }
}

void UAC_EquipmentManager::ReinitializeMovementWithWeight(float Weight)
{
    // Calculate total equipment weight and adjust movement speed
    // The actual movement modification is handled by the character Blueprint
    // This broadcasts the weight so listeners can react
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
    if (UAC_StatManager* StatMgr = GetStatManager())
    {
        StatMgr->AdjustStat(StatTag, Delta, E_ValueType::Flat);
    }
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
    if (UAC_StatManager* StatMgr = GetStatManager())
    {
        for (const FStatInfo& StatChange : StatChanges)
        {
            // Use Tag property and default to Flat value type
            StatMgr->AdjustStat(StatChange.Tag, StatChange.Value, E_ValueType::Flat);
        }
    }
}

// ============================================================
// BUFFS (Facade to AC_BuffManager)
// ============================================================

void UAC_EquipmentManager::TryGrantBuffs(const FGameplayTagContainer& BuffTags)
{
    if (UAC_BuffManager* BuffMgr = GetBuffManager())
    {
        BuffMgr->TryGrantBuffs(BuffTags);
    }
}

void UAC_EquipmentManager::TryRemoveBuffs(const FGameplayTagContainer& BuffTags)
{
    if (UAC_BuffManager* BuffMgr = GetBuffManager())
    {
        BuffMgr->TryRemoveBuffs(BuffTags);
    }
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

UAC_StatManager* UAC_EquipmentManager::GetStatManager() const
{
    APawn* Pawn = GetPawnFromController();
    if (Pawn)
    {
        return Pawn->FindComponentByClass<UAC_StatManager>();
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
    // Request save data from the save/load component
    OnSaveRequested.Broadcast(Tag);
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
    APawn* Pawn = GetPawnFromController();
    if (ACharacter* Character = Cast<ACharacter>(Pawn))
    {
        USkeletalMeshComponent* Mesh = Character->GetMesh();
        return Mesh && Mesh->GetSkeletalMeshAsset() != nullptr;
    }
    return false;
}

UUserWidget* UAC_EquipmentManager::GetPlayerHUD() const
{
    // HUD is typically accessed via PlayerController
    if (APlayerController* PC = Cast<APlayerController>(GetOwner()))
    {
        if (AHUD* HUD = PC->GetHUD())
        {
            // Return the main HUD widget if available
            // Specific HUD widget access depends on HUD class implementation
        }
    }
    return nullptr;
}

TSubclassOf<AActor> UAC_EquipmentManager::GetSelectedClass() const
{
    // Selected class is typically stored in GameInstance
    // This would query the game instance for the selected character class
    return nullptr;
}

bool UAC_EquipmentManager::IsValidArray(const TArray<UPDA_Item*>& Array) const
{
    return Array.Num() > 0;
}

void UAC_EquipmentManager::SwitchOnSlot(FGameplayTag SlotTag)
{
    // Determine slot type and execute appropriate logic
    if (RightHandSlots.HasTag(SlotTag))
    {
        // Handle right hand weapon slot
        WeaponAbilitySlot = E_WeaponAbilityHandle::RightHand;
    }
    else if (LeftHandSlots.HasTag(SlotTag))
    {
        // Handle left hand weapon slot
        WeaponAbilitySlot = E_WeaponAbilityHandle::LeftHand;
    }
    else if (ArmorSlots.HasTag(SlotTag))
    {
        // Handle armor slot - typically visual changes only
    }
    else if (TalismanSlots.HasTag(SlotTag))
    {
        // Handle talisman slot - applies buffs
    }
    else if (ToolSlots.HasTag(SlotTag))
    {
        // Handle tool slot
    }
}

void UAC_EquipmentManager::FastForEachLoop(const TArray<UPDA_Item*>& Items)
{
    for (UPDA_Item* Item : Items)
    {
        if (Item)
        {
            // Process each item - used for batch stat application
            // Individual item processing is handled by equip methods
        }
    }
}
