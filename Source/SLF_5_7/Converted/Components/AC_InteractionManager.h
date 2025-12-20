#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "Enums/E_ActionWeaponSlot.h"
#include "Enums/E_OverlayState.h"
#include "Enums/E_MovementType.h"
#include "Enums/E_InventorySlotType.h"
#include "Structs/FStatInfo.h"
#include "Structs/FReplenishInfo.h"
#include "AC_InteractionManager.generated.h"

class UAC_EquipmentManager;
class UAC_InventoryManager;
class UAC_StatManager;
class USceneComponent;
class UAC_BuffManager;
class UB_Stat;
class UPDA_Item;
class UUserWidget;
class APlayerController;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteractableDetected, AActor*, Interactable);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInteractableLost);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnTargetLocked_IM, AActor*, Target, bool, bLocked);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCloseAllMenus);

UCLASS(ClassGroup = (Custom), Blueprintable, meta = (BlueprintSpawnableComponent))
class SLF_5_7_API UAC_InteractionManager : public UActorComponent
{
    GENERATED_BODY()

public:
    UAC_InteractionManager();

    // ============================================================
    // PROPERTIES
    // ============================================================

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction")
    TObjectPtr<AActor> CurrentInteractable;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
    float InteractionRange;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LockOn")
    TObjectPtr<AActor> CurrentLockOnTarget;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
    bool bIsResting;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
    bool bInputEnabled;

    UPROPERTY(BlueprintReadWrite, Category = "LockOn")
    FTimerHandle TargetLockDistanceTimer;

    // ============================================================
    // DELEGATES
    // ============================================================

    UPROPERTY(BlueprintAssignable, Category = "Interaction")
    FOnInteractableDetected OnInteractableDetected;

    UPROPERTY(BlueprintAssignable, Category = "Interaction")
    FOnInteractableLost OnInteractableLost;

    UPROPERTY(BlueprintAssignable, Category = "LockOn")
    FOnTargetLocked_IM OnTargetLockedIM;

    UPROPERTY(BlueprintAssignable, Category = "Menu")
    FOnCloseAllMenus OnCloseAllMenus;

    // ============================================================
    // INTERACTION SYSTEM
    // ============================================================

    UFUNCTION(BlueprintCallable, Category = "Interaction")
    void TryInteract();

    UFUNCTION(BlueprintCallable, Category = "Interaction")
    void UpdateInteractable(AActor* NewInteractable);

    UFUNCTION(BlueprintPure, Category = "Interaction")
    bool HasInteractable() const;

    UFUNCTION(BlueprintCallable, Category = "Interaction")
    void OnInteractableTraced(AActor* TracedActor);

    UFUNCTION(BlueprintCallable, Category = "Interaction")
    void OnTraced(const FHitResult& HitResult);

    // ============================================================
    // LOCK-ON SYSTEM
    // ============================================================

    UFUNCTION(BlueprintCallable, Category = "LockOn")
    void LockOnTarget();

    UFUNCTION(BlueprintCallable, Category = "LockOn")
    void ResetLockOn();

    UFUNCTION(BlueprintCallable, Category = "LockOn")
    void OnTargetLocked(AActor* Target, bool bLocked);

    UFUNCTION(BlueprintCallable, Category = "LockOn")
    void ToggleLockonWidget(bool bVisible);

    UFUNCTION(BlueprintCallable, Category = "LockOn")
    bool TargetLockTrace(FHitResult& OutHit);

    UFUNCTION(BlueprintPure, Category = "LockOn")
    bool IsEnemyDead(AActor* Enemy) const;

    UFUNCTION(BlueprintPure, Category = "LockOn")
    bool ActorTagMatches(AActor* Actor, FName Tag) const;

    UFUNCTION(BlueprintPure, Category = "LockOn")
    USceneComponent* GetLockonComponent() const;

    UFUNCTION(BlueprintCallable, Category = "LockOn")
    void CheckTargetDistance();

    // ============================================================
    // CAMERA
    // ============================================================

    UFUNCTION(BlueprintCallable, Category = "Camera")
    void ResetCameraView();

    UFUNCTION(BlueprintCallable, Category = "Camera")
    void BlendViewTarget(AActor* NewViewTarget, float BlendTime);

    // ============================================================
    // MENU & UI
    // ============================================================

    UFUNCTION(BlueprintCallable, Category = "Menu")
    void CloseAllMenus();

    UFUNCTION(BlueprintPure, Category = "Menu")
    UUserWidget* GetInventoryWidget() const;

    UFUNCTION(BlueprintPure, Category = "Menu")
    UUserWidget* GetPlayerHUD() const;

    // ============================================================
    // INVENTORY MANAGEMENT
    // ============================================================

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    void ReplenishItem(UPDA_Item* Item);

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    void RemoveItem(UPDA_Item* Item, int32 Amount);

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    bool AddItem(UPDA_Item* Item, int32 Amount);

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    bool AddItemToStorage(UPDA_Item* Item, int32 Amount);

    UFUNCTION(BlueprintPure, Category = "Inventory")
    int32 GetSlotWithItem(UPDA_Item* Item) const;

    UFUNCTION(BlueprintPure, Category = "Inventory")
    int32 GetSlotWithItemTag(FGameplayTag ItemTag) const;

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

    UFUNCTION(BlueprintPure, Category = "Inventory")
    FReplenishInfo GetReplenishData(UPDA_Item* Item) const;

    UFUNCTION(BlueprintPure, Category = "Inventory")
    bool IsItemEquipped(UPDA_Item* Item) const;

    // ============================================================
    // EQUIPMENT
    // ============================================================

    UFUNCTION(BlueprintCallable, Category = "Equipment")
    void UnequipItemAtSlot(E_InventorySlotType SlotType, int32 SlotIndex);

    UFUNCTION(BlueprintCallable, Category = "Equipment")
    void UnequipWeaponAtSlot(E_ActionWeaponSlot WeaponSlot);

    UFUNCTION(BlueprintCallable, Category = "Equipment")
    void UnequipArmorAtSlot(int32 SlotIndex);

    UFUNCTION(BlueprintCallable, Category = "Equipment")
    void UnequipTalismanAtSlot(int32 SlotIndex);

    UFUNCTION(BlueprintCallable, Category = "Equipment")
    void UnequipToolAtSlot(int32 SlotIndex);

    UFUNCTION(BlueprintCallable, Category = "Equipment")
    void OnWeaponUnequip(E_ActionWeaponSlot WeaponSlot);

    UFUNCTION(BlueprintCallable, Category = "Equipment")
    void RefreshActiveGuardSequence();

    UFUNCTION(BlueprintCallable, Category = "Equipment")
    void ResetHeadpiece();

    UFUNCTION(BlueprintCallable, Category = "Equipment")
    void ResetArmor();

    UFUNCTION(BlueprintCallable, Category = "Equipment")
    void ResetGloves();

    UFUNCTION(BlueprintCallable, Category = "Equipment")
    void ResetGreaves();

    UFUNCTION(BlueprintPure, Category = "Equipment")
    bool AreBothWeaponSlotsActive() const;

    UFUNCTION(BlueprintPure, Category = "Equipment")
    E_ActionWeaponSlot GetActiveWeaponSlot() const;

    // ============================================================
    // STATS
    // ============================================================

    UFUNCTION(BlueprintPure, Category = "Stats")
    UB_Stat* GetStat(FGameplayTag StatTag) const;

    UFUNCTION(BlueprintCallable, Category = "Stats")
    void AdjustStat(FGameplayTag StatTag, float Delta);

    UFUNCTION(BlueprintCallable, Category = "Stats")
    void AdjustValue(UB_Stat* Stat, float Delta);

    UFUNCTION(BlueprintCallable, Category = "Stats")
    void ResetStat(FGameplayTag StatTag);

    UFUNCTION(BlueprintPure, Category = "Stats")
    float GetStatMaxValue(FGameplayTag StatTag) const;

    UFUNCTION(BlueprintPure, Category = "Stats")
    float GetStatCurrentValue(const FStatInfo& StatInfo) const;

    UFUNCTION(BlueprintCallable, Category = "Stats")
    void ApplyStatChanges(const TArray<FStatInfo>& StatChanges);

    // ============================================================
    // BUFFS
    // ============================================================

    UFUNCTION(BlueprintCallable, Category = "Buffs")
    void TryRemoveBuffs(const FGameplayTagContainer& BuffTags);

    UFUNCTION(BlueprintPure, Category = "Buffs")
    UAC_BuffManager* GetBuffManager() const;

    // ============================================================
    // MOVEMENT & STATE
    // ============================================================

    UFUNCTION(BlueprintCallable, Category = "Movement")
    void SetMovementMode(E_MovementType MovementType);

    UFUNCTION(BlueprintCallable, Category = "Movement")
    void UpdateOverlayStates(E_OverlayState NewState);

    UFUNCTION(BlueprintCallable, Category = "State")
    void ToggleInput(bool bEnabled);

    UFUNCTION(BlueprintCallable, Category = "State")
    void SetIsResting(bool bResting);

    // ============================================================
    // CONTROLLER ACCESS
    // ============================================================

    UFUNCTION(BlueprintPure, Category = "Controller")
    APlayerController* GetSoulslikeController() const;

    UFUNCTION(BlueprintPure, Category = "Controller")
    APawn* GetPawnFromController() const;

protected:
    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
