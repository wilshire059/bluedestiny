#include "PC_SoulslikeFramework.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "UserSettings/EnhancedInputUserSettings.h"
#include "Components/AC_InventoryManager.h"
#include "Components/AC_StatManager.h"
#include "Components/AC_ProgressManager.h"
#include "Components/AC_EquipmentManager.h"
#include "Components/AC_BuffManager.h"
#include "Components/AC_SaveLoadManager.h"
#include "Classes/B_Stat.h"
#include "Classes/B_PickupItem.h"
#include "Classes/B_RestingPoint.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

APC_SoulslikeFramework::APC_SoulslikeFramework()
{
	bIsInputEnabled = true;
	bIsRespawning = false;
}

void APC_SoulslikeFramework::BeginPlay()
{
	Super::BeginPlay();

	SetupDefaultInputContext();
	CreatePlayerHUD();
}

void APC_SoulslikeFramework::SetupInputComponent()
{
	Super::SetupInputComponent();
}

void APC_SoulslikeFramework::SetupDefaultInputContext()
{
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		if (DefaultMappingContext)
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
		if (GameplayMappingContext)
		{
			Subsystem->AddMappingContext(GameplayMappingContext, 1);
		}
	}
}

void APC_SoulslikeFramework::CreatePlayerHUD()
{
	if (PlayerHUDClass && IsLocalController())
	{
		PlayerHUD = CreateWidget<UUserWidget>(this, PlayerHUDClass);
		if (PlayerHUD)
		{
			PlayerHUD->AddToViewport();
		}
	}
}

//========================================
// BPI_Controller INTERFACE IMPLEMENTATIONS
//========================================

UUserWidget* APC_SoulslikeFramework::GetPlayerHUD_Implementation()
{
	return PlayerHUD;
}

void APC_SoulslikeFramework::RequestAddToSaveData_Implementation(FGameplayTag SaveTag, const FInstancedStruct& Data)
{
	// Add or update save data with the given tag
	bool bFound = false;
	for (int32 i = 0; i < SaveDataArray.Num(); i++)
	{
		// Check if this data matches the tag (implementation depends on your FInstancedStruct setup)
		// For now, just append
	}

	if (!bFound)
	{
		SaveDataArray.Add(Data);
	}
}

void APC_SoulslikeFramework::SetActiveWidgetForNavigation_Implementation(FGameplayTag NavigableWidgetTag)
{
	ActiveNavigableWidget = NavigableWidgetTag;
}

void APC_SoulslikeFramework::RequestUpdateSaveData_Implementation(FGameplayTag SaveTag, const TArray<FInstancedStruct>& Data)
{
	// Update entire save data array for the given tag
	// This would typically merge or replace data based on the tag
	for (const FInstancedStruct& NewData : Data)
	{
		SaveDataArray.Add(NewData);
	}
}

void APC_SoulslikeFramework::StartRespawn_Implementation(double FadeDelay)
{
	bIsRespawning = true;

	// Show "YOU DIED" message
	Execute_SendBigScreenMessage(this, FText::FromString(TEXT("YOU DIED")), nullptr, true, 0.5);

	// Switch to death input context
	TArray<UInputMappingContext*> Enable;
	TArray<UInputMappingContext*> Disable;

	if (DeathMappingContext)
	{
		Enable.Add(DeathMappingContext);
	}
	if (GameplayMappingContext)
	{
		Disable.Add(GameplayMappingContext);
	}
	if (DialogMappingContext)
	{
		Disable.Add(DialogMappingContext);
	}
	if (MainMenuMappingContext)
	{
		Disable.Add(MainMenuMappingContext);
	}

	Execute_SwitchInputContext(this, Enable, Disable);

	// Set timer for respawn
	FTimerHandle RespawnTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(RespawnTimerHandle, this, &APC_SoulslikeFramework::OnRespawnTimerComplete, FadeDelay, false);
}

void APC_SoulslikeFramework::OnRespawnTimerComplete()
{
	bIsRespawning = false;
	OnRespawnComplete.Broadcast();
}

void APC_SoulslikeFramework::SendBigScreenMessage_Implementation(const FText& Text, UMaterialInterface* GradientMaterial, bool bBackdrop, double PlayRate)
{
	// This would create and display a large screen message widget
	// Implementation depends on your W_BigScreenMessage widget class
	// For now, this is a stub that Blueprint children can override
}

int32 APC_SoulslikeFramework::GetCurrency_Implementation()
{
	return GetCurrentCurrency();
}

void APC_SoulslikeFramework::AdjustCurrency_Implementation(int32 Delta)
{
	AdjustCurrencyAmount(Delta);
}

void APC_SoulslikeFramework::SerializeDataForSaving_Implementation(uint8 Behavior, FGameplayTag SaveTag)
{
	// Serialize data for the specific tag based on behavior
	TArray<FInstancedStruct> OutData;

	// Route to appropriate serialization based on the tag
	// This is typically done by matching the SaveTag to known categories
	// and calling the appropriate Serialize* function
}

void APC_SoulslikeFramework::ShowSavingVisual_Implementation(double Length)
{
	// Display a saving indicator on the HUD
	// Implementation depends on your W_PlayerHUD having a saving indicator
}

void APC_SoulslikeFramework::SwitchInputContext_Implementation(const TArray<UInputMappingContext*>& ContextsToEnable, const TArray<UInputMappingContext*>& ContextsToDisable)
{
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		// Remove contexts to disable
		for (UInputMappingContext* Context : ContextsToDisable)
		{
			if (Context)
			{
				Subsystem->RemoveMappingContext(Context);
			}
		}

		// Add contexts to enable
		for (UInputMappingContext* Context : ContextsToEnable)
		{
			if (Context)
			{
				Subsystem->AddMappingContext(Context, 0);
			}
		}
	}
}

UAC_ProgressManager* APC_SoulslikeFramework::GetProgressManager_Implementation()
{
	return ProgressManager;
}

void APC_SoulslikeFramework::BlendViewTarget_Implementation(AActor* TargetActor, double BlendTime, double BlendExp, bool bLockOutgoing)
{
	if (TargetActor)
	{
		FViewTargetTransitionParams TransitionParams;
		TransitionParams.BlendTime = BlendTime;
		TransitionParams.BlendExp = BlendExp;
		TransitionParams.bLockOutgoing = bLockOutgoing;

		SetViewTargetWithBlend(TargetActor, BlendTime, VTBlend_Cubic, BlendExp, bLockOutgoing);
	}
}

void APC_SoulslikeFramework::ToggleRadarUpdateState_Implementation(bool bUpdateEnabled)
{
	ToggleUpdateState(bUpdateEnabled);
}

void APC_SoulslikeFramework::SerializeAllDataForSaving_Implementation(uint8 Behavior)
{
	SaveDataArray.Empty();

	TArray<FInstancedStruct> TempData;

	// Serialize all data categories
	SerializeStatsData(TempData);
	SaveDataArray.Append(TempData);
	TempData.Empty();

	SerializeEquipmentData(TempData);
	SaveDataArray.Append(TempData);
	TempData.Empty();

	SerializeInventoryStorageCurrencyData(TempData);
	SaveDataArray.Append(TempData);
	TempData.Empty();

	SerializeProgressData(TempData);
	SaveDataArray.Append(TempData);
	TempData.Empty();

	SerializeVendorData(TempData);
	SaveDataArray.Append(TempData);
	TempData.Empty();

	SerializeInteractableStates(TempData);
	SaveDataArray.Append(TempData);
	TempData.Empty();

	SerializeItemWheelData(TempData);
	SaveDataArray.Append(TempData);
	TempData.Empty();

	SerializeClassData(TempData);
	SaveDataArray.Append(TempData);
	TempData.Empty();

	SerializeLevelData(TempData);
	SaveDataArray.Append(TempData);
}

APlayerController* APC_SoulslikeFramework::GetSoulslikeController_Implementation()
{
	return this;
}

void APC_SoulslikeFramework::ToggleInput_Implementation(bool bEnabled)
{
	bIsInputEnabled = bEnabled;

	if (bEnabled)
	{
		EnableInput(this);
	}
	else
	{
		DisableInput(this);
	}
}

APawn* APC_SoulslikeFramework::GetPawnFromController_Implementation()
{
	return GetPawn();
}

void APC_SoulslikeFramework::LootItemToInventory_Implementation(AB_PickupItem* Item)
{
	LootPickupItem(Item);
}

UAC_InventoryManager* APC_SoulslikeFramework::GetInventoryComponent_Implementation()
{
	return InventoryManager;
}

//========================================
// STAT FUNCTIONS
//========================================

UB_Stat* APC_SoulslikeFramework::GetStat(FGameplayTag StatTag)
{
	if (StatManager)
	{
		return StatManager->GetStat(StatTag);
	}
	return nullptr;
}

float APC_SoulslikeFramework::GetStatCurrentValue(FGameplayTag StatTag) const
{
	if (StatManager)
	{
		if (UB_Stat* Stat = StatManager->GetStat(StatTag))
		{
			return Stat->CurrentValue;
		}
	}
	return 0.0f;
}

float APC_SoulslikeFramework::GetStatMaxValue(FGameplayTag StatTag) const
{
	if (StatManager)
	{
		if (UB_Stat* Stat = StatManager->GetStat(StatTag))
		{
			return Stat->MaxValue;
		}
	}
	return 0.0f;
}

void APC_SoulslikeFramework::AdjustStat(FGameplayTag StatTag, float Delta)
{
	if (StatManager)
	{
		StatManager->ModifyStat(StatTag, Delta, E_ValueType::Current);
	}
}

void APC_SoulslikeFramework::AdjustValue(UB_Stat* Stat, float Delta)
{
	if (Stat)
	{
		Stat->ModifyStat(Delta);
	}
}

void APC_SoulslikeFramework::ResetStat(FGameplayTag StatTag)
{
	if (StatManager)
	{
		if (UB_Stat* Stat = StatManager->GetStat(StatTag))
		{
			Stat->SetCurrentValue(Stat->MaxValue);
		}
	}
}

void APC_SoulslikeFramework::ApplyStatChanges(const TArray<FStatInfo>& StatChanges)
{
	if (InventoryManager)
	{
		InventoryManager->ApplyStatChanges(StatChanges);
	}
}

TArray<FStatInfo> APC_SoulslikeFramework::GetAllStats() const
{
	TArray<FStatInfo> AllStats;

	if (StatManager)
	{
		for (const auto& StatPair : StatManager->Stats)
		{
			if (UB_Stat* Stat = StatPair.Value)
			{
				FStatInfo Info;
				Info.Tag = StatPair.Key;
				Info.Value = Stat->CurrentValue;
				Info.MaxValue = Stat->MaxValue;
				AllStats.Add(Info);
			}
		}
	}

	return AllStats;
}

//========================================
// INVENTORY FUNCTIONS
//========================================

void APC_SoulslikeFramework::AddItem(UPDA_Item* Item, int32 Count)
{
	if (InventoryManager)
	{
		InventoryManager->AddItem(Item, Count);
	}
}

void APC_SoulslikeFramework::RemoveItem(UPDA_Item* Item, int32 Count)
{
	if (InventoryManager)
	{
		InventoryManager->RemoveItem(Item, Count);
	}
}

bool APC_SoulslikeFramework::AddItemToStorage(UPDA_Item* Item, int32 Count)
{
	if (InventoryManager)
	{
		return InventoryManager->AddItemToStorage(Item, Count);
	}
	return false;
}

UPDA_Item* APC_SoulslikeFramework::GetItemAtSlot(E_InventorySlotType SlotType, int32 SlotIndex) const
{
	if (InventoryManager)
	{
		return InventoryManager->GetItemAtSlot(SlotType, SlotIndex);
	}
	return nullptr;
}

int32 APC_SoulslikeFramework::GetSlotWithItem(UPDA_Item* Item) const
{
	if (InventoryManager)
	{
		return InventoryManager->GetSlotWithItem(Item);
	}
	return -1;
}

int32 APC_SoulslikeFramework::GetSlotWithItemTag(FGameplayTag ItemTag, E_InventorySlotType SlotType) const
{
	if (InventoryManager)
	{
		return InventoryManager->GetSlotWithItemTag(ItemTag, SlotType);
	}
	return -1;
}

int32 APC_SoulslikeFramework::GetEmptySlot() const
{
	if (InventoryManager)
	{
		return InventoryManager->GetEmptySlot();
	}
	return -1;
}

void APC_SoulslikeFramework::AddNewSlots(int32 Count)
{
	if (InventoryManager)
	{
		InventoryManager->AddNewSlots(Count);
	}
}

int32 APC_SoulslikeFramework::GetTotalInventoryItemsCount() const
{
	if (InventoryManager)
	{
		return InventoryManager->GetTotalInventoryItemsCount();
	}
	return 0;
}

int32 APC_SoulslikeFramework::GetTotalStorageItemsCount() const
{
	if (InventoryManager)
	{
		return InventoryManager->GetTotalStorageItemsCount();
	}
	return 0;
}

void APC_SoulslikeFramework::LootPickupItem(AB_PickupItem* Item)
{
	if (InventoryManager && Item)
	{
		// Get item data from pickup and add to inventory
		// Implementation depends on AB_PickupItem interface
	}
}

UUserWidget* APC_SoulslikeFramework::GetInventoryWidget() const
{
	if (InventoryManager)
	{
		return InventoryManager->GetInventoryWidget();
	}
	return nullptr;
}

//========================================
// EQUIPMENT FUNCTIONS
//========================================

void APC_SoulslikeFramework::UnequipItemAtSlot(E_InventorySlotType SlotType, int32 SlotIndex)
{
	if (InventoryManager)
	{
		InventoryManager->UnequipItemAtSlot(SlotType, SlotIndex);
	}
}

void APC_SoulslikeFramework::UnequipWeaponAtSlot(E_ActionWeaponSlot WeaponSlot)
{
	if (InventoryManager)
	{
		InventoryManager->UnequipWeaponAtSlot(WeaponSlot);
	}
}

void APC_SoulslikeFramework::UnequipArmorAtSlot(int32 SlotIndex)
{
	if (InventoryManager)
	{
		InventoryManager->UnequipArmorAtSlot(SlotIndex);
	}
}

void APC_SoulslikeFramework::UnequipTalismanAtSlot(int32 SlotIndex)
{
	if (InventoryManager)
	{
		InventoryManager->UnequipTalismanAtSlot(SlotIndex);
	}
}

void APC_SoulslikeFramework::UnequipToolAtSlot(int32 SlotIndex)
{
	if (InventoryManager)
	{
		InventoryManager->UnequipToolAtSlot(SlotIndex);
	}
}

void APC_SoulslikeFramework::OnWeaponUnequip(E_ActionWeaponSlot WeaponSlot)
{
	if (InventoryManager)
	{
		InventoryManager->OnWeaponUnequip(WeaponSlot);
	}
}

void APC_SoulslikeFramework::RefreshActiveGuardSequence()
{
	if (InventoryManager)
	{
		InventoryManager->RefreshActiveGuardSequence();
	}
}

void APC_SoulslikeFramework::ResetHeadpiece()
{
	if (InventoryManager)
	{
		InventoryManager->ResetHeadpiece();
	}
}

void APC_SoulslikeFramework::ResetArmor()
{
	if (InventoryManager)
	{
		InventoryManager->ResetArmor();
	}
}

void APC_SoulslikeFramework::ResetGloves()
{
	if (InventoryManager)
	{
		InventoryManager->ResetGloves();
	}
}

void APC_SoulslikeFramework::ResetGreaves()
{
	if (InventoryManager)
	{
		InventoryManager->ResetGreaves();
	}
}

bool APC_SoulslikeFramework::AreBothWeaponSlotsActive() const
{
	if (InventoryManager)
	{
		return InventoryManager->AreBothWeaponSlotsActive();
	}
	return false;
}

E_ActionWeaponSlot APC_SoulslikeFramework::GetActiveWeaponSlot() const
{
	if (InventoryManager)
	{
		return InventoryManager->GetActiveWeaponSlot();
	}
	return E_ActionWeaponSlot::Right;
}

bool APC_SoulslikeFramework::IsItemEquipped(UPDA_Item* Item) const
{
	if (InventoryManager)
	{
		return InventoryManager->IsItemEquipped(Item);
	}
	return false;
}

void APC_SoulslikeFramework::UpdateOverlayStates(E_OverlayState NewState)
{
	if (InventoryManager)
	{
		InventoryManager->UpdateOverlayStates(NewState);
	}
}

//========================================
// BUFF FUNCTIONS
//========================================

void APC_SoulslikeFramework::TryRemoveBuffs(const FGameplayTagContainer& BuffTags)
{
	if (InventoryManager)
	{
		InventoryManager->TryRemoveBuffs(BuffTags);
	}
}

UAC_BuffManager* APC_SoulslikeFramework::GetBuffManager() const
{
	if (InventoryManager)
	{
		return InventoryManager->GetBuffManager();
	}
	return nullptr;
}

//========================================
// CURRENCY FUNCTIONS
//========================================

int32 APC_SoulslikeFramework::GetCurrentCurrency() const
{
	if (InventoryManager)
	{
		return InventoryManager->GetCurrentCurrency();
	}
	return 0;
}

void APC_SoulslikeFramework::AdjustCurrencyAmount(int32 Delta)
{
	if (InventoryManager)
	{
		InventoryManager->AdjustCurrency(Delta);
	}
}

//========================================
// MOVEMENT FUNCTIONS
//========================================

void APC_SoulslikeFramework::SetMovementMode(E_MovementType MovementType)
{
	if (InventoryManager)
	{
		InventoryManager->SetMovementMode(MovementType);
	}
}

//========================================
// SAVE/LOAD FUNCTIONS
//========================================

FString APC_SoulslikeFramework::GetSavedLevelName() const
{
	return SavedLevelName;
}

bool APC_SoulslikeFramework::GetDataByTag(FGameplayTag SaveTag, FInstancedStruct& OutData) const
{
	// Search through SaveDataArray for matching tag
	// Implementation depends on how you've structured your FInstancedStruct data
	return false;
}

void APC_SoulslikeFramework::SerializeStatsData(TArray<FInstancedStruct>& OutData)
{
	// Serialize all stat data
	if (StatManager)
	{
		for (const auto& StatPair : StatManager->Stats)
		{
			if (UB_Stat* Stat = StatPair.Value)
			{
				FStatInfo Info;
				Info.Tag = StatPair.Key;
				Info.Value = Stat->CurrentValue;
				Info.MaxValue = Stat->MaxValue;

				FInstancedStruct InstancedData;
				InstancedData.InitializeAs<FStatInfo>(Info);
				OutData.Add(InstancedData);
			}
		}
	}
}

void APC_SoulslikeFramework::SerializeEquipmentData(TArray<FInstancedStruct>& OutData)
{
	// Serialize equipment data through EquipmentManager
	if (EquipmentManager)
	{
		TArray<FEquipmentItemsSaveInfo> SaveInfo;
		EquipmentManager->ConvertToEquipmentItemsSaveInfoStructs(SaveInfo);

		for (const FEquipmentItemsSaveInfo& Info : SaveInfo)
		{
			FInstancedStruct InstancedData;
			InstancedData.InitializeAs<FEquipmentItemsSaveInfo>(Info);
			OutData.Add(InstancedData);
		}
	}
}

void APC_SoulslikeFramework::SerializeInventoryStorageCurrencyData(TArray<FInstancedStruct>& OutData)
{
	// Serialize inventory, storage, and currency
	if (InventoryManager)
	{
		// Add inventory items
		for (const FInventoryItem& Item : InventoryManager->Inventory)
		{
			FInstancedStruct InstancedData;
			InstancedData.InitializeAs<FInventoryItem>(Item);
			OutData.Add(InstancedData);
		}
	}
}

void APC_SoulslikeFramework::SerializeProgressData(TArray<FInstancedStruct>& OutData)
{
	// Serialize progress data through ProgressManager
	if (ProgressManager)
	{
		// Implementation depends on ProgressManager structure
	}
}

void APC_SoulslikeFramework::SerializeVendorData(TArray<FInstancedStruct>& OutData)
{
	// Serialize vendor/shop data
	// Implementation depends on how vendor data is structured
}

void APC_SoulslikeFramework::SerializeInteractableStates(TArray<FInstancedStruct>& OutData)
{
	// Serialize the state of all interactables (opened chests, activated switches, etc.)
	// Implementation depends on how interactable states are tracked
}

void APC_SoulslikeFramework::SerializeItemWheelData(TArray<FInstancedStruct>& OutData)
{
	// Serialize item wheel configuration
	if (EquipmentManager)
	{
		// Get item wheel slots and serialize
	}
}

void APC_SoulslikeFramework::SerializeClassData(TArray<FInstancedStruct>& OutData)
{
	// Serialize selected class
	FGameplayTag SelectedClass = GetSelectedClass();
	// Package into FInstancedStruct
}

void APC_SoulslikeFramework::SerializeLevelData(TArray<FInstancedStruct>& OutData)
{
	// Serialize current level name
	SavedLevelName = UGameplayStatics::GetCurrentLevelName(GetWorld());
}

FGameplayTag APC_SoulslikeFramework::GetSelectedClass() const
{
	// Get selected class from the player character or save system
	if (APawn* ControlledPawn = GetPawn())
	{
		// Implementation depends on how class selection is stored
	}
	return FGameplayTag();
}

FVector APC_SoulslikeFramework::GetRestingPointSpawnPosition() const
{
	// Get the last resting point's spawn position
	if (APawn* ControlledPawn = GetPawn())
	{
		// Check if pawn has last resting point data
		return ControlledPawn->GetActorLocation();
	}
	return FVector::ZeroVector;
}

AB_RestingPoint* APC_SoulslikeFramework::GetNearestRestingPoint() const
{
	// Find nearest resting point in the world
	TArray<AActor*> RestingPoints;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AB_RestingPoint::StaticClass(), RestingPoints);

	if (APawn* ControlledPawn = GetPawn())
	{
		FVector PawnLocation = ControlledPawn->GetActorLocation();
		float NearestDistance = TNumericLimits<float>::Max();
		AB_RestingPoint* NearestPoint = nullptr;

		for (AActor* Actor : RestingPoints)
		{
			float Distance = FVector::Dist(PawnLocation, Actor->GetActorLocation());
			if (Distance < NearestDistance)
			{
				NearestDistance = Distance;
				NearestPoint = Cast<AB_RestingPoint>(Actor);
			}
		}

		return NearestPoint;
	}

	return nullptr;
}

//========================================
// UI FUNCTIONS
//========================================

void APC_SoulslikeFramework::HandleMainMenuRequest()
{
	if (GameMenu)
	{
		bool bIsVisible = GameMenu->IsVisible();

		if (bIsVisible)
		{
			GameMenu->SetVisibility(ESlateVisibility::Collapsed);
		}
		else
		{
			GameMenu->SetVisibility(ESlateVisibility::Visible);
		}

		OnMenuVisibilityChanged.Broadcast(!bIsVisible);
	}
	else if (GameMenuClass && IsLocalController())
	{
		GameMenu = CreateWidget<UUserWidget>(this, GameMenuClass);
		if (GameMenu)
		{
			GameMenu->AddToViewport(10);
			OnMenuVisibilityChanged.Broadcast(true);
		}
	}
}

bool APC_SoulslikeFramework::GetGameMenuVisibility() const
{
	return GameMenu && GameMenu->IsVisible();
}

bool APC_SoulslikeFramework::GetTargetWidgetVisibility() const
{
	return TargetWidget && TargetWidget->IsVisible();
}

bool APC_SoulslikeFramework::GetDialogWindowVisibility() const
{
	return DialogWindow && DialogWindow->IsVisible();
}

UEnhancedInputUserSettings* APC_SoulslikeFramework::GetInputUserSettings() const
{
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		return Subsystem->GetUserSettings();
	}
	return nullptr;
}

//========================================
// RADAR FUNCTIONS
//========================================

void APC_SoulslikeFramework::ToggleUpdateState(bool bEnabled)
{
	// Toggle radar update state
	// Implementation depends on how the radar component is structured
}

//========================================
// UTILITY FUNCTIONS
//========================================

UAnimInstance* APC_SoulslikeFramework::GetSoulslikeAnimInstance() const
{
	if (APawn* ControlledPawn = GetPawn())
	{
		if (ACharacter* ControlledCharacter = Cast<ACharacter>(ControlledPawn))
		{
			if (USkeletalMeshComponent* Mesh = ControlledCharacter->GetMesh())
			{
				return Mesh->GetAnimInstance();
			}
		}
	}
	return nullptr;
}

UAC_EquipmentManager* APC_SoulslikeFramework::GetEquipmentManager() const
{
	return EquipmentManager;
}

UAC_StatManager* APC_SoulslikeFramework::GetStatManager() const
{
	return StatManager;
}

UAC_SaveLoadManager* APC_SoulslikeFramework::GetSaveLoadManager() const
{
	return SaveLoadManager;
}
