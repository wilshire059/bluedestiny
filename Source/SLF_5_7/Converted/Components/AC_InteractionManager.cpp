#include "AC_InteractionManager.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Character.h"
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
    // Would call BPI_GenericCharacter::ToggleLockonWidget on the target
    // Placeholder: implementation depends on the character class
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
    // Placeholder: implementation depends on UI system
}

UUserWidget* UAC_InteractionManager::GetInventoryWidget() const
{
    // Placeholder: implementation depends on UI system
    return nullptr;
}

UUserWidget* UAC_InteractionManager::GetPlayerHUD() const
{
    // Placeholder: implementation depends on UI system
    return nullptr;
}

// ============================================================
// INVENTORY MANAGEMENT
// Note: These functions delegate to AC_InventoryManager when fully migrated
// ============================================================

void UAC_InteractionManager::ReplenishItem(UPDA_Item* Item)
{
    // Placeholder: requires AC_InventoryManager::ReplenishItem
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
    // Placeholder: requires AC_InventoryManager::AddItemToStorage
    return false;
}

int32 UAC_InteractionManager::GetSlotWithItem(UPDA_Item* Item) const
{
    // Placeholder: requires AC_InventoryManager::GetSlotWithItem
    return -1;
}

int32 UAC_InteractionManager::GetSlotWithItemTag(FGameplayTag ItemTag) const
{
    // Placeholder: requires AC_InventoryManager::GetSlotWithItemTag with proper signature
    return -1;
}

UPDA_Item* UAC_InteractionManager::GetItemAtSlot(E_InventorySlotType SlotType, int32 SlotIndex) const
{
    // Placeholder: requires AC_InventoryManager::GetItemAtSlot
    return nullptr;
}

int32 UAC_InteractionManager::GetEmptySlot() const
{
    // Placeholder: requires AC_InventoryManager::GetEmptySlot
    return -1;
}

void UAC_InteractionManager::AddNewSlots(int32 Count)
{
    // Placeholder: requires AC_InventoryManager::AddNewSlots
}

int32 UAC_InteractionManager::GetTotalInventoryItemsCount() const
{
    // Placeholder: requires AC_InventoryManager::GetTotalInventoryItemsCount
    return 0;
}

int32 UAC_InteractionManager::GetTotalStorageItemsCount() const
{
    // Placeholder: requires AC_InventoryManager::GetTotalStorageItemsCount
    return 0;
}

FReplenishInfo UAC_InteractionManager::GetReplenishData(UPDA_Item* Item) const
{
    // This would typically be retrieved from a resting point
    return FReplenishInfo();
}

bool UAC_InteractionManager::IsItemEquipped(UPDA_Item* Item) const
{
    // Placeholder: requires AC_EquipmentManager::IsItemEquipped
    return false;
}

// ============================================================
// EQUIPMENT
// Note: These functions delegate to AC_EquipmentManager when fully migrated
// ============================================================

void UAC_InteractionManager::UnequipItemAtSlot(E_InventorySlotType SlotType, int32 SlotIndex)
{
    // Placeholder: requires AC_EquipmentManager::UnequipItemAtSlot
}

void UAC_InteractionManager::UnequipWeaponAtSlot(E_ActionWeaponSlot WeaponSlot)
{
    // Placeholder: requires AC_EquipmentManager with E_ActionWeaponSlot signature
}

void UAC_InteractionManager::UnequipArmorAtSlot(int32 SlotIndex)
{
    // Placeholder: requires AC_EquipmentManager::UnequipArmorAtSlot
}

void UAC_InteractionManager::UnequipTalismanAtSlot(int32 SlotIndex)
{
    // Placeholder: requires AC_EquipmentManager with int32 signature
}

void UAC_InteractionManager::UnequipToolAtSlot(int32 SlotIndex)
{
    // Placeholder: requires AC_EquipmentManager with int32 signature
}

void UAC_InteractionManager::OnWeaponUnequip(E_ActionWeaponSlot WeaponSlot)
{
    // Placeholder: requires AC_EquipmentManager::OnWeaponUnequip
}

void UAC_InteractionManager::RefreshActiveGuardSequence()
{
    // Placeholder: requires AC_EquipmentManager::RefreshActiveGuardSequence
}

void UAC_InteractionManager::ResetHeadpiece()
{
    // Placeholder: requires AC_EquipmentManager::ResetHeadpiece
}

void UAC_InteractionManager::ResetArmor()
{
    // Placeholder: requires AC_EquipmentManager::ResetArmor
}

void UAC_InteractionManager::ResetGloves()
{
    // Placeholder: requires AC_EquipmentManager::ResetGloves
}

void UAC_InteractionManager::ResetGreaves()
{
    // Placeholder: requires AC_EquipmentManager::ResetGreaves
}

bool UAC_InteractionManager::AreBothWeaponSlotsActive() const
{
    // Placeholder: requires AC_EquipmentManager::AreBothWeaponSlotsActive
    return false;
}

E_ActionWeaponSlot UAC_InteractionManager::GetActiveWeaponSlot() const
{
    // Placeholder: requires AC_EquipmentManager with proper return type
    return E_ActionWeaponSlot::RightHand;
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
    // Placeholder: requires AC_StatManager::AdjustStat
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
    // Placeholder: requires AC_StatManager::ResetStat
}

float UAC_InteractionManager::GetStatMaxValue(FGameplayTag StatTag) const
{
    // Placeholder: requires AC_StatManager::GetStatMaxValue
    return 0.0f;
}

float UAC_InteractionManager::GetStatCurrentValue(const FStatInfo& StatInfo) const
{
    return StatInfo.Value;
}

void UAC_InteractionManager::ApplyStatChanges(const TArray<FStatInfo>& StatChanges)
{
    // Placeholder: requires AC_StatManager::ApplyStatChanges
}

// ============================================================
// BUFFS
// ============================================================

void UAC_InteractionManager::TryRemoveBuffs(const FGameplayTagContainer& BuffTags)
{
    // Placeholder: requires AC_BuffManager::TryRemoveBuffs
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
    // Placeholder: requires character interface implementation
}

void UAC_InteractionManager::UpdateOverlayStates(E_OverlayState NewState)
{
    // Placeholder: requires character interface implementation
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
