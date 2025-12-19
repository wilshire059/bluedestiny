#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "Enums/E_OverlayState.h"
#include "Enums/E_MovementType.h"
#include "Enums/E_ActionWeaponSlot.h"
#include "Enums/E_WeaponAbilityHandle.h"
#include "Structs/FStatInfo.h"
#include "Structs/FEquipmentItemsSaveInfo.h"
#include "AC_EquipmentManager.generated.h"

class UPDA_Item;
class UB_Stat;
class UAC_BuffManager;
class UAC_SaveLoadManager;
class UAC_StatManager;
class UUserWidget;
class AB_Item;
class UAnimSequenceBase;
class USkeletalMesh;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnEquipmentChanged, FGameplayTag, Slot, const UPDA_Item*, Item);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnWeaponEquipDelegate, UPDA_Item*, Item, bool, bRightHand);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWeaponUnequipDelegate, E_ActionWeaponSlot, WeaponSlot);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWeaponAbilityUpdated);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWeaponAbilityRemoved);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWeaponStatCheckFailed);

UCLASS(ClassGroup = (Custom), Blueprintable, meta = (BlueprintSpawnableComponent))
class SLF_5_7_API UAC_EquipmentManager : public UActorComponent
{
    GENERATED_BODY()

public:
    UAC_EquipmentManager();

    // ============================================================
    // PROPERTIES
    // ============================================================

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
    TMap<FGameplayTag, TObjectPtr<UPDA_Item>> CurrentEquipment;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
    TMap<FGameplayTag, TObjectPtr<AB_Item>> SpawnedItemsAtSlots;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
    TArray<TObjectPtr<UPDA_Item>> AllEquippedItems;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
    TArray<TObjectPtr<UPDA_Item>> HiddenItems;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment|Weapon")
    FGameplayTagContainer RightHandSlots;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment|Weapon")
    FGameplayTagContainer LeftHandSlots;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment|Wheel")
    TObjectPtr<UUserWidget> ItemWheel_RightHand;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment|Wheel")
    TObjectPtr<UUserWidget> ItemWheel_LeftHand;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment|Wheel")
    TObjectPtr<UUserWidget> ItemWheel_Tools;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment|Overlay")
    E_OverlayState RightHandOverlayState;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment|Overlay")
    E_OverlayState LeftHandOverlayState;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment|Overlay")
    FGameplayTagContainer RightHandOverlayTags;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment|Overlay")
    FGameplayTagContainer LeftHandOverlayTags;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment|Guard")
    TObjectPtr<UAnimSequenceBase> Guard_R;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment|Guard")
    TObjectPtr<UAnimSequenceBase> Guard_L;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment|Guard")
    TObjectPtr<UAnimSequenceBase> ActiveBlockSequence;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment|Stats")
    TArray<FStatInfo> ActiveStats;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment|Tags")
    FGameplayTagContainer GrantedTags;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment|State")
    bool bIsAsyncWeaponBusy;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment|State")
    bool bIsCrouched;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment|Save")
    TArray<FEquipmentItemsSaveInfo> Cached_LoadedEquipment;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment|Active")
    FGameplayTag ActiveSlot;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment|Active")
    E_WeaponAbilityHandle WeaponAbilitySlot;

    // ============================================================
    // DELEGATES
    // ============================================================

    UPROPERTY(BlueprintAssignable, Category = "Equipment")
    FOnEquipmentChanged OnEquipmentChanged;

    UPROPERTY(BlueprintAssignable, Category = "Equipment")
    FOnWeaponEquipDelegate OnWeaponEquipDelegate;

    UPROPERTY(BlueprintAssignable, Category = "Equipment")
    FOnWeaponUnequipDelegate OnWeaponUnequipDelegate;

    UPROPERTY(BlueprintAssignable, Category = "Equipment|Ability")
    FOnWeaponAbilityUpdated OnWeaponAbilityUpdated;

    UPROPERTY(BlueprintAssignable, Category = "Equipment|Ability")
    FOnWeaponAbilityRemoved OnWeaponAbilityRemoved;

    UPROPERTY(BlueprintAssignable, Category = "Equipment|Stats")
    FOnWeaponStatCheckFailed OnWeaponStatCheckFailed;

    // ============================================================
    // WEAPON EQUIP/UNEQUIP
    // ============================================================

    UFUNCTION(BlueprintCallable, Category = "Equipment|Weapon")
    void EquipWeaponToSlot(UPDA_Item* Item, FGameplayTag SlotTag);

    UFUNCTION(BlueprintCallable, Category = "Equipment|Weapon")
    void UnequipWeaponAtSlot(E_ActionWeaponSlot WeaponSlot);

    UFUNCTION(BlueprintCallable, Category = "Equipment|Weapon")
    void OnWeaponEquip(UPDA_Item* Item, bool bRightHand);

    UFUNCTION(BlueprintCallable, Category = "Equipment|Weapon")
    void OnWeaponUnequip(E_ActionWeaponSlot WeaponSlot);

    UFUNCTION(BlueprintCallable, Category = "Equipment|Weapon")
    void WieldItemAtSlot(FGameplayTag SlotTag);

    UFUNCTION(BlueprintCallable, Category = "Equipment|Weapon")
    void AsyncSpawnAndEquipWeapon(FGameplayTag SlotTag, UPDA_Item* Item);

    // ============================================================
    // ARMOR EQUIP/UNEQUIP
    // ============================================================

    UFUNCTION(BlueprintCallable, Category = "Equipment|Armor")
    void EquipArmorToSlot(UPDA_Item* Item, FGameplayTag SlotTag);

    UFUNCTION(BlueprintCallable, Category = "Equipment|Armor")
    void UnequipArmorAtSlot(int32 SlotIndex);

    UFUNCTION(BlueprintCallable, Category = "Equipment|Armor")
    void ChangeHeadpiece(USkeletalMesh* NewMesh);

    UFUNCTION(BlueprintCallable, Category = "Equipment|Armor")
    void ChangeArmor(USkeletalMesh* NewMesh);

    UFUNCTION(BlueprintCallable, Category = "Equipment|Armor")
    void ChangeGloves(USkeletalMesh* NewMesh);

    UFUNCTION(BlueprintCallable, Category = "Equipment|Armor")
    void ChangeGreaves(USkeletalMesh* NewMesh);

    UFUNCTION(BlueprintCallable, Category = "Equipment|Armor")
    void ResetHeadpiece();

    UFUNCTION(BlueprintCallable, Category = "Equipment|Armor")
    void ResetArmor();

    UFUNCTION(BlueprintCallable, Category = "Equipment|Armor")
    void ResetGloves();

    UFUNCTION(BlueprintCallable, Category = "Equipment|Armor")
    void ResetGreaves();

    // ============================================================
    // TALISMAN/TOOL EQUIP/UNEQUIP
    // ============================================================

    UFUNCTION(BlueprintCallable, Category = "Equipment|Talisman")
    void EquipTalismanToSlot(UPDA_Item* Item, FGameplayTag SlotTag);

    UFUNCTION(BlueprintCallable, Category = "Equipment|Talisman")
    void UnequipTalismanAtSlot(int32 SlotIndex);

    UFUNCTION(BlueprintCallable, Category = "Equipment|Tool")
    void EquipToolToSlot(UPDA_Item* Item, FGameplayTag SlotTag);

    UFUNCTION(BlueprintCallable, Category = "Equipment|Tool")
    void UnequipToolAtSlot(int32 SlotIndex);

    // ============================================================
    // GENERIC EQUIP/UNEQUIP
    // ============================================================

    UFUNCTION(BlueprintCallable, Category = "Equipment")
    void UnequipItemAtSlot(FGameplayTag SlotTag, int32 SlotIndex);

    UFUNCTION(BlueprintPure, Category = "Equipment")
    UPDA_Item* GetItemAtSlot(FGameplayTag SlotTag) const;

    UFUNCTION(BlueprintPure, Category = "Equipment")
    bool IsSlotOccupied(FGameplayTag SlotTag) const;

    // ============================================================
    // WEAPON STATE
    // ============================================================

    UFUNCTION(BlueprintPure, Category = "Equipment|Weapon")
    E_ActionWeaponSlot GetActiveWeaponSlot() const;

    UFUNCTION(BlueprintPure, Category = "Equipment|Weapon")
    bool AreBothWeaponSlotsActive() const;

    UFUNCTION(BlueprintPure, Category = "Equipment|Weapon")
    bool GetTwoHandStance() const;

    UFUNCTION(BlueprintCallable, Category = "Equipment|Weapon")
    void RefreshActiveGuardSequence();

    UFUNCTION(BlueprintPure, Category = "Equipment|Weapon")
    int32 GetActiveWheelSlotForWeapon(bool bRightHand) const;

    UFUNCTION(BlueprintPure, Category = "Equipment|Tool")
    int32 GetActiveWheelSlotForTool() const;

    // ============================================================
    // OVERLAY & MOVEMENT
    // ============================================================

    UFUNCTION(BlueprintCallable, Category = "Equipment|Overlay")
    void UpdateOverlayStates(E_OverlayState NewState);

    UFUNCTION(BlueprintCallable, Category = "Equipment|Movement")
    void SetMovementMode(E_MovementType MovementType);

    UFUNCTION(BlueprintCallable, Category = "Equipment|Movement")
    void ReinitializeMovementWithWeight(float Weight);

    UFUNCTION(BlueprintPure, Category = "Equipment|Movement")
    bool GetIsCrouched() const;

    // ============================================================
    // STATS (Facade to AC_StatManager)
    // ============================================================

    UFUNCTION(BlueprintPure, Category = "Equipment|Stats")
    UB_Stat* GetStat(FGameplayTag StatTag) const;

    UFUNCTION(BlueprintCallable, Category = "Equipment|Stats")
    void AdjustStat(FGameplayTag StatTag, float Delta);

    UFUNCTION(BlueprintCallable, Category = "Equipment|Stats")
    void AdjustValue(UB_Stat* Stat, float Delta);

    UFUNCTION(BlueprintCallable, Category = "Equipment|Stats")
    void ApplyStatChanges(const TArray<FStatInfo>& StatChanges);

    // ============================================================
    // BUFFS (Facade to AC_BuffManager)
    // ============================================================

    UFUNCTION(BlueprintCallable, Category = "Equipment|Buffs")
    void TryGrantBuffs(const FGameplayTagContainer& BuffTags);

    UFUNCTION(BlueprintCallable, Category = "Equipment|Buffs")
    void TryRemoveBuffs(const FGameplayTagContainer& BuffTags);

    UFUNCTION(BlueprintPure, Category = "Equipment|Buffs")
    UAC_BuffManager* GetBuffManager() const;

    // ============================================================
    // SAVE/LOAD
    // ============================================================

    UFUNCTION(BlueprintCallable, Category = "Equipment|Save")
    void ConvertToEquipmentItemsSaveInfoStructs(TArray<FEquipmentItemsSaveInfo>& OutSaveInfo);

    UFUNCTION(BlueprintCallable, Category = "Equipment|Save")
    void InitLoadedItems(const TArray<FEquipmentItemsSaveInfo>& LoadedItems);

    UFUNCTION(BlueprintPure, Category = "Equipment|Save")
    UAC_SaveLoadManager* GetSaveLoadComponent() const;

    UFUNCTION(BlueprintCallable, Category = "Equipment|Save")
    void GetSaveDataByTag(FGameplayTag Tag);

    // ============================================================
    // HELPERS
    // ============================================================

    UFUNCTION(BlueprintPure, Category = "Equipment|Helper")
    APawn* GetPawnFromController() const;

    UFUNCTION(BlueprintPure, Category = "Equipment|Helper")
    bool GetMeshInitialized() const;

    UFUNCTION(BlueprintPure, Category = "Equipment|Helper")
    UUserWidget* GetPlayerHUD() const;

    UFUNCTION(BlueprintPure, Category = "Equipment|Helper")
    TSubclassOf<AActor> GetSelectedClass() const;

    UFUNCTION(BlueprintPure, Category = "Equipment|Helper")
    bool IsValidArray(const TArray<UPDA_Item*>& Array) const;

    UFUNCTION(BlueprintCallable, Category = "Equipment|Helper")
    void SwitchOnSlot(FGameplayTag SlotTag);

    UFUNCTION(BlueprintCallable, Category = "Equipment|Helper")
    void FastForEachLoop(const TArray<UPDA_Item*>& Items);

protected:
    virtual void BeginPlay() override;
};
