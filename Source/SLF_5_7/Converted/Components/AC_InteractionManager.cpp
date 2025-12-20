#include "AC_InteractionManager.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Character.h"
#include "GameFramework/HUD.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "TimerManager.h"
#include "Components/SceneComponent.h"
#include "Components/AC_EquipmentManager.h"
#include "Components/AC_InventoryManager.h"
#include "Components/AC_StatManager.h"
#include "Components/AC_BuffManager.h"
#include "Components/AC_CombatManager.h"
#include "Classes/B_Stat.h"
#include "DataAssets/PDA_Item.h"
#include "Interfaces/BPI_Interactable.h"
#include "Interfaces/BPI_Generic_Character.h"
#include "Enums/E_ValueType.h"

UAC_InteractionManager::UAC_InteractionManager()
{
    PrimaryComponentTick.bCanEverTick = true;
    CurrentInteractable = nullptr;
    CurrentLockOnTarget = nullptr;
    InteractionRange = 200.0f;
    bIsResting = false;
    bInputEnabled = true;
}

void UAC_InteractionManager::BeginPlay()
{
    Super::BeginPlay();
}

void UAC_InteractionManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

// ============================================================
// INTERACTION SYSTEM
// ============================================================

void UAC_InteractionManager::TryInteract()
{
    if (!CurrentInteractable)
    {
        return;
    }

    // Call interaction through interface
    if (CurrentInteractable->Implements<UBPI_Interactable>())
    {
        IBPI_Interactable::Execute_OnInteract(CurrentInteractable, GetOwner());
    }
}

void UAC_InteractionManager::UpdateInteractable(AActor* NewInteractable)
{
    if (CurrentInteractable != NewInteractable)
    {
        AActor* OldInteractable = CurrentInteractable;
        CurrentInteractable = NewInteractable;

        if (NewInteractable)
        {
            OnInteractableDetected.Broadcast(NewInteractable);
        }
        else if (OldInteractable)
        {
            OnInteractableLost.Broadcast();
        }
    }
}

bool UAC_InteractionManager::HasInteractable() const
{
    return CurrentInteractable != nullptr;
}

void UAC_InteractionManager::OnInteractableTraced(AActor* TracedActor)
{
    if (TracedActor && TracedActor->Implements<UBPI_Interactable>())
    {
        UpdateInteractable(TracedActor);
    }
    else
    {
        UpdateInteractable(nullptr);
    }
}

void UAC_InteractionManager::OnTraced(const FHitResult& HitResult)
{
    if (HitResult.bBlockingHit && HitResult.GetActor())
    {
        OnInteractableTraced(HitResult.GetActor());
    }
    else
    {
        OnInteractableTraced(nullptr);
    }
}

// ============================================================
// LOCK-ON SYSTEM
// ============================================================

void UAC_InteractionManager::LockOnTarget()
{
    // Start timer to check target distance periodically
    if (UWorld* World = GetWorld())
    {
        World->GetTimerManager().SetTimer(
            TargetLockDistanceTimer,
            this,
            &UAC_InteractionManager::CheckTargetDistance,
            1.0f,
            true
        );
    }

    // Toggle lock-on widget visibility
    ToggleLockonWidget(true);

    // Broadcast lock-on event
    OnTargetLockedIM.Broadcast(CurrentLockOnTarget, true);
}

void UAC_InteractionManager::ResetLockOn()
{
    // Clear timer
    if (UWorld* World = GetWorld())
    {
        World->GetTimerManager().ClearTimer(TargetLockDistanceTimer);
    }

    // Hide lock-on widget
    ToggleLockonWidget(false);

    // Clear current target
    CurrentLockOnTarget = nullptr;

    // Broadcast lock-off event
    OnTargetLockedIM.Broadcast(nullptr, false);
}

void UAC_InteractionManager::OnTargetLocked(AActor* Target, bool bLocked)
{
    CurrentLockOnTarget = bLocked ? Target : nullptr;
    OnTargetLockedIM.Broadcast(Target, bLocked);
}

void UAC_InteractionManager::ToggleLockonWidget(bool bVisible)
{
    // Widget toggling is handled via the target actor's interface
    // Character Blueprint should implement BPI_GenericCharacter to handle this
    if (CurrentLockOnTarget && CurrentLockOnTarget->Implements<UBPI_Generic_Character>())
    {
        IBPI_Generic_Character::Execute_ToggleLockonWidget(CurrentLockOnTarget, bVisible);
    }
}

bool UAC_InteractionManager::TargetLockTrace(FHitResult& OutHit)
{
    AActor* Owner = GetOwner();
    if (!Owner)
    {
        return false;
    }

    // Perform sphere trace for lockable targets
    FVector Start = Owner->GetActorLocation();
    FVector End = Start + Owner->GetActorForwardVector() * 2000.0f;

    TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
    ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));

    TArray<AActor*> IgnoreActors;
    IgnoreActors.Add(Owner);

    return UKismetSystemLibrary::SphereTraceSingleForObjects(
        this,
        Start,
        End,
        100.0f,
        ObjectTypes,
        false,
        IgnoreActors,
        EDrawDebugTrace::None,
        OutHit,
        true
    );
}

bool UAC_InteractionManager::IsEnemyDead(AActor* Enemy) const
{
    if (!Enemy)
    {
        return true;
    }

    // Check if enemy has combat manager and is dead
    if (UAC_CombatManager* CombatManager = Enemy->FindComponentByClass<UAC_CombatManager>())
    {
        return CombatManager->bIsDead;
    }

    return false;
}

bool UAC_InteractionManager::ActorTagMatches(AActor* Actor, FName Tag) const
{
    if (!Actor)
    {
        return false;
    }
    return Actor->ActorHasTag(Tag);
}

USceneComponent* UAC_InteractionManager::GetLockonComponent() const
{
    APawn* Pawn = GetPawnFromController();
    if (Pawn)
    {
        // Returns the scene component used for lock-on widget attachment
        return Pawn->FindComponentByClass<USceneComponent>();
    }
    return nullptr;
}

void UAC_InteractionManager::CheckTargetDistance()
{
    if (!CurrentLockOnTarget)
    {
        ResetLockOn();
        return;
    }

    AActor* Owner = GetOwner();
    if (!Owner)
    {
        return;
    }

    // Check if target is dead
    if (IsEnemyDead(CurrentLockOnTarget))
    {
        ResetLockOn();
        return;
    }

    // Check distance to target
    float Distance = FVector::Dist(Owner->GetActorLocation(), CurrentLockOnTarget->GetActorLocation());
    if (Distance > 3000.0f)
    {
        ResetLockOn();
    }
}

// ============================================================
// CAMERA
// ============================================================

void UAC_InteractionManager::ResetCameraView()
{
    if (APlayerController* PC = GetSoulslikeController())
    {
        APawn* Pawn = PC->GetPawn();
        if (Pawn)
        {
            PC->SetViewTarget(Pawn);
        }
    }
}

void UAC_InteractionManager::BlendViewTarget(AActor* NewViewTarget, float BlendTime)
{
    if (APlayerController* PC = GetSoulslikeController())
    {
        PC->SetViewTargetWithBlend(NewViewTarget, BlendTime, EViewTargetBlendFunction::VTBlend_Linear, 0.0f, false);
    }
}

// ============================================================
// MENU & UI
// ============================================================

void UAC_InteractionManager::CloseAllMenus()
{
    // Broadcast event for UI system to handle menu closing
    OnCloseAllMenus.Broadcast();
}

UUserWidget* UAC_InteractionManager::GetInventoryWidget() const
{
    // Inventory widget is typically cached or accessed via HUD
    // Returns nullptr - actual implementation handled in Blueprint HUD
    return nullptr;
}

UUserWidget* UAC_InteractionManager::GetPlayerHUD() const
{
    if (APlayerController* PC = GetSoulslikeController())
    {
        if (AHUD* HUD = PC->GetHUD())
        {
            // HUD widget access depends on specific HUD implementation
        }
    }
    return nullptr;
}

// ============================================================
// INVENTORY MANAGEMENT
// Note: These functions delegate to AC_InventoryManager when fully migrated
// ============================================================

void UAC_InteractionManager::ReplenishItem(UPDA_Item* Item)
{
    APawn* Pawn = GetPawnFromController();
    if (Pawn)
    {
        if (UAC_InventoryManager* InvMgr = Pawn->FindComponentByClass<UAC_InventoryManager>())
        {
            InvMgr->ReplenishItem(Item);
        }
    }
}

void UAC_InteractionManager::RemoveItem(UPDA_Item* Item, int32 Amount)
{
    APawn* Pawn = GetPawnFromController();
    if (Pawn)
    {
        if (UAC_InventoryManager* InvMgr = Pawn->FindComponentByClass<UAC_InventoryManager>())
        {
            InvMgr->RemoveItem(Item, Amount);
        }
    }
}

bool UAC_InteractionManager::AddItem(UPDA_Item* Item, int32 Amount)
{
    APawn* Pawn = GetPawnFromController();
    if (Pawn)
    {
        if (UAC_InventoryManager* InvMgr = Pawn->FindComponentByClass<UAC_InventoryManager>())
        {
            InvMgr->AddItem(Item, Amount);
            return true;
        }
    }
    return false;
}

bool UAC_InteractionManager::AddItemToStorage(UPDA_Item* Item, int32 Amount)
{
    APawn* Pawn = GetPawnFromController();
    if (Pawn)
    {
        if (UAC_InventoryManager* InvMgr = Pawn->FindComponentByClass<UAC_InventoryManager>())
        {
            return InvMgr->AddItemToStorage(Item, Amount);
        }
    }
    return false;
}

int32 UAC_InteractionManager::GetSlotWithItem(UPDA_Item* Item) const
{
    APawn* Pawn = GetPawnFromController();
    if (Pawn)
    {
        if (UAC_InventoryManager* InvMgr = Pawn->FindComponentByClass<UAC_InventoryManager>())
        {
            return InvMgr->GetSlotWithItem(Item);
        }
    }
    return -1;
}

int32 UAC_InteractionManager::GetSlotWithItemTag(FGameplayTag ItemTag) const
{
    APawn* Pawn = GetPawnFromController();
    if (Pawn)
    {
        if (UAC_InventoryManager* InvMgr = Pawn->FindComponentByClass<UAC_InventoryManager>())
        {
            return InvMgr->GetSlotWithItemTag(ItemTag, E_InventorySlotType::InventorySlot);
        }
    }
    return -1;
}

UPDA_Item* UAC_InteractionManager::GetItemAtSlot(E_InventorySlotType SlotType, int32 SlotIndex) const
{
    APawn* Pawn = GetPawnFromController();
    if (Pawn)
    {
        if (UAC_InventoryManager* InvMgr = Pawn->FindComponentByClass<UAC_InventoryManager>())
        {
            return InvMgr->GetItemAtSlot(SlotType, SlotIndex);
        }
    }
    return nullptr;
}

int32 UAC_InteractionManager::GetEmptySlot() const
{
    APawn* Pawn = GetPawnFromController();
    if (Pawn)
    {
        if (UAC_InventoryManager* InvMgr = Pawn->FindComponentByClass<UAC_InventoryManager>())
        {
            return InvMgr->GetEmptySlot();
        }
    }
    return -1;
}

void UAC_InteractionManager::AddNewSlots(int32 Count)
{
    APawn* Pawn = GetPawnFromController();
    if (Pawn)
    {
        if (UAC_InventoryManager* InvMgr = Pawn->FindComponentByClass<UAC_InventoryManager>())
        {
            InvMgr->AddNewSlots(Count);
        }
    }
}

int32 UAC_InteractionManager::GetTotalInventoryItemsCount() const
{
    APawn* Pawn = GetPawnFromController();
    if (Pawn)
    {
        if (UAC_InventoryManager* InvMgr = Pawn->FindComponentByClass<UAC_InventoryManager>())
        {
            return InvMgr->GetTotalInventoryItemsCount();
        }
    }
    return 0;
}

int32 UAC_InteractionManager::GetTotalStorageItemsCount() const
{
    APawn* Pawn = GetPawnFromController();
    if (Pawn)
    {
        if (UAC_InventoryManager* InvMgr = Pawn->FindComponentByClass<UAC_InventoryManager>())
        {
            return InvMgr->GetTotalStorageItemsCount();
        }
    }
    return 0;
}

FReplenishInfo UAC_InteractionManager::GetReplenishData(UPDA_Item* Item) const
{
    // This would typically be retrieved from a resting point
    return FReplenishInfo();
}

bool UAC_InteractionManager::IsItemEquipped(UPDA_Item* Item) const
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
// EQUIPMENT
// Note: These functions delegate to AC_EquipmentManager when fully migrated
// ============================================================

void UAC_InteractionManager::UnequipItemAtSlot(E_InventorySlotType SlotType, int32 SlotIndex)
{
    APawn* Pawn = GetPawnFromController();
    if (Pawn)
    {
        if (UAC_EquipmentManager* EquipMgr = Pawn->FindComponentByClass<UAC_EquipmentManager>())
        {
            // Get the slot tag based on slot type and index
            // The actual tag mapping depends on how slots are configured
        }
    }
}

void UAC_InteractionManager::UnequipWeaponAtSlot(E_ActionWeaponSlot WeaponSlot)
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

void UAC_InteractionManager::UnequipArmorAtSlot(int32 SlotIndex)
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

void UAC_InteractionManager::UnequipTalismanAtSlot(int32 SlotIndex)
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

void UAC_InteractionManager::UnequipToolAtSlot(int32 SlotIndex)
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

void UAC_InteractionManager::OnWeaponUnequip(E_ActionWeaponSlot WeaponSlot)
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

void UAC_InteractionManager::RefreshActiveGuardSequence()
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

void UAC_InteractionManager::ResetHeadpiece()
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

void UAC_InteractionManager::ResetArmor()
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

void UAC_InteractionManager::ResetGloves()
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

void UAC_InteractionManager::ResetGreaves()
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

bool UAC_InteractionManager::AreBothWeaponSlotsActive() const
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

E_ActionWeaponSlot UAC_InteractionManager::GetActiveWeaponSlot() const
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

// ============================================================
// STATS
// Note: These functions delegate to AC_StatManager when fully migrated
// ============================================================

UB_Stat* UAC_InteractionManager::GetStat(FGameplayTag StatTag) const
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

void UAC_InteractionManager::AdjustStat(FGameplayTag StatTag, float Delta)
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

void UAC_InteractionManager::AdjustValue(UB_Stat* Stat, float Delta)
{
    if (Stat)
    {
        Stat->ModifyStat(Delta);
    }
}

void UAC_InteractionManager::ResetStat(FGameplayTag StatTag)
{
    APawn* Pawn = GetPawnFromController();
    if (Pawn)
    {
        if (UAC_StatManager* StatMgr = Pawn->FindComponentByClass<UAC_StatManager>())
        {
            if (UB_Stat* Stat = StatMgr->GetStat(StatTag))
            {
                Stat->ResetToBase();
            }
        }
    }
}

float UAC_InteractionManager::GetStatMaxValue(FGameplayTag StatTag) const
{
    APawn* Pawn = GetPawnFromController();
    if (Pawn)
    {
        if (UAC_StatManager* StatMgr = Pawn->FindComponentByClass<UAC_StatManager>())
        {
            if (UB_Stat* Stat = StatMgr->GetStat(StatTag))
            {
                return Stat->MaxValue;
            }
        }
    }
    return 0.0f;
}

float UAC_InteractionManager::GetStatCurrentValue(const FStatInfo& StatInfo) const
{
    return StatInfo.Value;
}

void UAC_InteractionManager::ApplyStatChanges(const TArray<FStatInfo>& StatChanges)
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
// BUFFS
// ============================================================

void UAC_InteractionManager::TryRemoveBuffs(const FGameplayTagContainer& BuffTags)
{
    if (UAC_BuffManager* BuffMgr = GetBuffManager())
    {
        BuffMgr->TryRemoveBuffs(BuffTags);
    }
}

UAC_BuffManager* UAC_InteractionManager::GetBuffManager() const
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

void UAC_InteractionManager::SetMovementMode(E_MovementType MovementType)
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

void UAC_InteractionManager::UpdateOverlayStates(E_OverlayState NewState)
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

void UAC_InteractionManager::ToggleInput(bool bEnabled)
{
    bInputEnabled = bEnabled;

    if (APlayerController* PC = GetSoulslikeController())
    {
        if (bEnabled)
        {
            PC->EnableInput(PC);
        }
        else
        {
            PC->DisableInput(PC);
        }
    }
}

void UAC_InteractionManager::SetIsResting(bool bResting)
{
    bIsResting = bResting;
}

// ============================================================
// CONTROLLER ACCESS
// ============================================================

APlayerController* UAC_InteractionManager::GetSoulslikeController() const
{
    AActor* Owner = GetOwner();
    if (!Owner)
    {
        return nullptr;
    }

    // If owner is a controller, return it directly
    if (APlayerController* PC = Cast<APlayerController>(Owner))
    {
        return PC;
    }

    // If owner is a pawn, get its controller
    if (APawn* Pawn = Cast<APawn>(Owner))
    {
        return Cast<APlayerController>(Pawn->GetController());
    }

    return nullptr;
}

APawn* UAC_InteractionManager::GetPawnFromController() const
{
    if (APlayerController* PC = GetSoulslikeController())
    {
        return PC->GetPawn();
    }

    // If owner is already a pawn, return it
    return Cast<APawn>(GetOwner());
}
