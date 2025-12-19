#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Interfaces/BPI_Controller.h"
#include "GameplayTagContainer.h"
#include "StructUtils/InstancedStruct.h"
#include "Structs/FStatInfo.h"
#include "Enums/E_InventorySlotType.h"
#include "Enums/E_ActionWeaponSlot.h"
#include "Enums/E_MovementType.h"
#include "Enums/E_OverlayState.h"
#include "PC_SoulslikeFramework.generated.h"

class UInputMappingContext;
class UAC_InventoryManager;
class UAC_StatManager;
class UAC_ProgressManager;
class UAC_EquipmentManager;
class UAC_BuffManager;
class UAC_SaveLoadManager;
class UB_Stat;
class UPDA_Item;
class AB_PickupItem;
class UUserWidget;
class UAnimInstance;
class UEnhancedInputUserSettings;
class AB_RestingPoint;

// Delegates
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRespawnComplete);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFadeOutComplete);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMenuVisibilityChanged, bool, bVisible);

UCLASS()
class SLF_5_7_API APC_SoulslikeFramework : public APlayerController, public IBPI_Controller
{
	GENERATED_BODY()

public:
	APC_SoulslikeFramework();

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

public:
	//========================================
	// COMPONENTS
	//========================================

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UAC_InventoryManager> InventoryManager;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UAC_StatManager> StatManager;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UAC_ProgressManager> ProgressManager;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UAC_EquipmentManager> EquipmentManager;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UAC_SaveLoadManager> SaveLoadManager;

	//========================================
	// INPUT PROPERTIES
	//========================================

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputMappingContext> GameplayMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputMappingContext> DeathMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputMappingContext> DialogMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputMappingContext> MainMenuMappingContext;

	//========================================
	// UI PROPERTIES
	//========================================

	UPROPERTY(BlueprintReadOnly, Category = "UI")
	TObjectPtr<UUserWidget> PlayerHUD;

	UPROPERTY(BlueprintReadOnly, Category = "UI")
	TObjectPtr<UUserWidget> GameMenu;

	UPROPERTY(BlueprintReadOnly, Category = "UI")
	TObjectPtr<UUserWidget> DialogWindow;

	UPROPERTY(BlueprintReadOnly, Category = "UI")
	TObjectPtr<UUserWidget> TargetWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> PlayerHUDClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> GameMenuClass;

	//========================================
	// STATE PROPERTIES
	//========================================

	UPROPERTY(BlueprintReadOnly, Category = "State")
	bool bIsInputEnabled;

	UPROPERTY(BlueprintReadOnly, Category = "State")
	bool bIsRespawning;

	UPROPERTY(BlueprintReadOnly, Category = "State")
	FGameplayTag ActiveNavigableWidget;

	//========================================
	// SAVE DATA PROPERTIES
	//========================================

	UPROPERTY(BlueprintReadWrite, Category = "Save")
	TArray<FInstancedStruct> SaveDataArray;

	UPROPERTY(BlueprintReadWrite, Category = "Save")
	FString SavedLevelName;

	//========================================
	// DELEGATES
	//========================================

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnRespawnComplete OnRespawnComplete;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnFadeOutComplete OnFadeOutComplete;

	UPROPERTY(BlueprintAssignable, Category = "Events|UI")
	FOnMenuVisibilityChanged OnMenuVisibilityChanged;

	//========================================
	// BPI_Controller INTERFACE IMPLEMENTATIONS
	//========================================

	virtual UUserWidget* GetPlayerHUD_Implementation() override;
	virtual void RequestAddToSaveData_Implementation(FGameplayTag SaveTag, const FInstancedStruct& Data) override;
	virtual void SetActiveWidgetForNavigation_Implementation(FGameplayTag NavigableWidgetTag) override;
	virtual void RequestUpdateSaveData_Implementation(FGameplayTag SaveTag, const TArray<FInstancedStruct>& Data) override;
	virtual void StartRespawn_Implementation(double FadeDelay) override;
	virtual void SendBigScreenMessage_Implementation(const FText& Text, UMaterialInterface* GradientMaterial, bool bBackdrop, double PlayRate) override;
	virtual int32 GetCurrency_Implementation() override;
	virtual void AdjustCurrency_Implementation(int32 Delta) override;
	virtual void SerializeDataForSaving_Implementation(uint8 Behavior, FGameplayTag SaveTag) override;
	virtual void ShowSavingVisual_Implementation(double Length) override;
	virtual void SwitchInputContext_Implementation(const TArray<UInputMappingContext*>& ContextsToEnable, const TArray<UInputMappingContext*>& ContextsToDisable) override;
	virtual UAC_ProgressManager* GetProgressManager_Implementation() override;
	virtual void BlendViewTarget_Implementation(AActor* TargetActor, double BlendTime, double BlendExp, bool bLockOutgoing) override;
	virtual void ToggleRadarUpdateState_Implementation(bool bUpdateEnabled) override;
	virtual void SerializeAllDataForSaving_Implementation(uint8 Behavior) override;
	virtual APlayerController* GetSoulslikeController_Implementation() override;
	virtual void ToggleInput_Implementation(bool bEnabled) override;
	virtual APawn* GetPawnFromController_Implementation() override;
	virtual void LootItemToInventory_Implementation(AB_PickupItem* Item) override;
	virtual UAC_InventoryManager* GetInventoryComponent_Implementation() override;

	//========================================
	// STAT FUNCTIONS
	//========================================

	UFUNCTION(BlueprintCallable, Category = "Stats")
	UB_Stat* GetStat(FGameplayTag StatTag);

	UFUNCTION(BlueprintPure, Category = "Stats")
	float GetStatCurrentValue(FGameplayTag StatTag) const;

	UFUNCTION(BlueprintPure, Category = "Stats")
	float GetStatMaxValue(FGameplayTag StatTag) const;

	UFUNCTION(BlueprintCallable, Category = "Stats")
	void AdjustStat(FGameplayTag StatTag, float Delta);

	UFUNCTION(BlueprintCallable, Category = "Stats")
	void AdjustValue(UB_Stat* Stat, float Delta);

	UFUNCTION(BlueprintCallable, Category = "Stats")
	void ResetStat(FGameplayTag StatTag);

	UFUNCTION(BlueprintCallable, Category = "Stats")
	void ApplyStatChanges(const TArray<FStatInfo>& StatChanges);

	UFUNCTION(BlueprintPure, Category = "Stats")
	TArray<FStatInfo> GetAllStats() const;

	//========================================
	// INVENTORY FUNCTIONS
	//========================================

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void AddItem(UPDA_Item* Item, int32 Count);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void RemoveItem(UPDA_Item* Item, int32 Count);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool AddItemToStorage(UPDA_Item* Item, int32 Count);

	UFUNCTION(BlueprintPure, Category = "Inventory")
	UPDA_Item* GetItemAtSlot(E_InventorySlotType SlotType, int32 SlotIndex) const;

	UFUNCTION(BlueprintPure, Category = "Inventory")
	int32 GetSlotWithItem(UPDA_Item* Item) const;

	UFUNCTION(BlueprintPure, Category = "Inventory")
	int32 GetSlotWithItemTag(FGameplayTag ItemTag, E_InventorySlotType SlotType) const;

	UFUNCTION(BlueprintPure, Category = "Inventory")
	int32 GetEmptySlot() const;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void AddNewSlots(int32 Count);

	UFUNCTION(BlueprintPure, Category = "Inventory")
	int32 GetTotalInventoryItemsCount() const;

	UFUNCTION(BlueprintPure, Category = "Inventory")
	int32 GetTotalStorageItemsCount() const;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void LootPickupItem(AB_PickupItem* Item);

	UFUNCTION(BlueprintPure, Category = "Inventory")
	UUserWidget* GetInventoryWidget() const;

	//========================================
	// EQUIPMENT FUNCTIONS
	//========================================

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

	UFUNCTION(BlueprintPure, Category = "Equipment")
	bool IsItemEquipped(UPDA_Item* Item) const;

	UFUNCTION(BlueprintCallable, Category = "Equipment")
	void UpdateOverlayStates(E_OverlayState NewState);

	//========================================
	// BUFF FUNCTIONS
	//========================================

	UFUNCTION(BlueprintCallable, Category = "Buffs")
	void TryRemoveBuffs(const FGameplayTagContainer& BuffTags);

	UFUNCTION(BlueprintPure, Category = "Buffs")
	UAC_BuffManager* GetBuffManager() const;

	//========================================
	// CURRENCY FUNCTIONS
	//========================================

	UFUNCTION(BlueprintPure, Category = "Currency")
	int32 GetCurrentCurrency() const;

	UFUNCTION(BlueprintCallable, Category = "Currency")
	void AdjustCurrencyAmount(int32 Delta);

	//========================================
	// MOVEMENT FUNCTIONS
	//========================================

	UFUNCTION(BlueprintCallable, Category = "Movement")
	void SetMovementMode(E_MovementType MovementType);

	//========================================
	// SAVE/LOAD FUNCTIONS
	//========================================

	UFUNCTION(BlueprintPure, Category = "Save")
	FString GetSavedLevelName() const;

	UFUNCTION(BlueprintCallable, Category = "Save")
	bool GetDataByTag(FGameplayTag SaveTag, FInstancedStruct& OutData) const;

	UFUNCTION(BlueprintCallable, Category = "Save")
	void SerializeStatsData(TArray<FInstancedStruct>& OutData);

	UFUNCTION(BlueprintCallable, Category = "Save")
	void SerializeEquipmentData(TArray<FInstancedStruct>& OutData);

	UFUNCTION(BlueprintCallable, Category = "Save")
	void SerializeInventoryStorageCurrencyData(TArray<FInstancedStruct>& OutData);

	UFUNCTION(BlueprintCallable, Category = "Save")
	void SerializeProgressData(TArray<FInstancedStruct>& OutData);

	UFUNCTION(BlueprintCallable, Category = "Save")
	void SerializeVendorData(TArray<FInstancedStruct>& OutData);

	UFUNCTION(BlueprintCallable, Category = "Save")
	void SerializeInteractableStates(TArray<FInstancedStruct>& OutData);

	UFUNCTION(BlueprintCallable, Category = "Save")
	void SerializeItemWheelData(TArray<FInstancedStruct>& OutData);

	UFUNCTION(BlueprintCallable, Category = "Save")
	void SerializeClassData(TArray<FInstancedStruct>& OutData);

	UFUNCTION(BlueprintCallable, Category = "Save")
	void SerializeLevelData(TArray<FInstancedStruct>& OutData);

	UFUNCTION(BlueprintPure, Category = "Save")
	FGameplayTag GetSelectedClass() const;

	UFUNCTION(BlueprintCallable, Category = "Save")
	FVector GetRestingPointSpawnPosition() const;

	UFUNCTION(BlueprintCallable, Category = "Save")
	AB_RestingPoint* GetNearestRestingPoint() const;

	//========================================
	// UI FUNCTIONS
	//========================================

	UFUNCTION(BlueprintCallable, Category = "UI")
	void HandleMainMenuRequest();

	UFUNCTION(BlueprintPure, Category = "UI")
	bool GetGameMenuVisibility() const;

	UFUNCTION(BlueprintPure, Category = "UI")
	bool GetTargetWidgetVisibility() const;

	UFUNCTION(BlueprintPure, Category = "UI")
	bool GetDialogWindowVisibility() const;

	UFUNCTION(BlueprintPure, Category = "UI")
	UEnhancedInputUserSettings* GetInputUserSettings() const;

	//========================================
	// RADAR FUNCTIONS
	//========================================

	UFUNCTION(BlueprintCallable, Category = "Radar")
	void ToggleUpdateState(bool bEnabled);

	//========================================
	// UTILITY FUNCTIONS
	//========================================

	UFUNCTION(BlueprintPure, Category = "Utility")
	UAnimInstance* GetSoulslikeAnimInstance() const;

	UFUNCTION(BlueprintPure, Category = "Utility")
	UAC_EquipmentManager* GetEquipmentManager() const;

	UFUNCTION(BlueprintPure, Category = "Utility")
	UAC_StatManager* GetStatManager() const;

	UFUNCTION(BlueprintPure, Category = "Utility")
	UAC_SaveLoadManager* GetSaveLoadManager() const;

protected:
	//========================================
	// INTERNAL HELPERS
	//========================================

	void SetupDefaultInputContext();
	void CreatePlayerHUD();

	UFUNCTION()
	void OnRespawnTimerComplete();
};
