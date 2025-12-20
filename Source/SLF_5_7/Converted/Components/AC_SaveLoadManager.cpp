#include "AC_SaveLoadManager.h"
#include "Kismet/GameplayStatics.h"
#include "Interfaces/BPI_GameInstance.h"

UAC_SaveLoadManager::UAC_SaveLoadManager()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UAC_SaveLoadManager::BeginPlay()
{
    Super::BeginPlay();

    // Sequence: Update slot then preload
    UpdateActiveSlot();
    TryPreloadData();
}

// ============================================================
// INITIALIZATION
// ============================================================

void UAC_SaveLoadManager::UpdateActiveSlot()
{
    UGameInstance* GI = UGameplayStatics::GetGameInstance(this);
    if (GI && GI->Implements<UBPI_GameInstance>())
    {
        IBPI_GameInstance::Execute_GetActiveSlotName(GI, CurrentSaveSlot);
    }
}

FString UAC_SaveLoadManager::GetActiveSlotName() const
{
    return CurrentSaveSlot;
}

void UAC_SaveLoadManager::TryPreloadData()
{
    if (CurrentSaveSlot.IsEmpty())
    {
        return;
    }

    if (UGameplayStatics::DoesSaveGameExist(CurrentSaveSlot, 0))
    {
        USaveGame* LoadedGame = UGameplayStatics::LoadGameFromSlot(CurrentSaveSlot, 0);
        if (USG_SoulslikeFramework* SG = Cast<USG_SoulslikeFramework>(LoadedGame))
        {
            CurrentSaveGameObject = SG;
            Data = SG->GetSavedData();
            OnDataLoaded.Broadcast(Data);
        }
    }
}

// ============================================================
// SAVE/LOAD
// ============================================================

void UAC_SaveLoadManager::SaveData(const FSaveGameInfo& DataToSave)
{
    if (CurrentSaveSlot.IsEmpty())
    {
        UpdateActiveSlot();
        if (CurrentSaveSlot.IsEmpty()) return;
    }

    // Create save game object
    USG_SoulslikeFramework* SaveInstance = Cast<USG_SoulslikeFramework>(
        UGameplayStatics::CreateSaveGameObject(USG_SoulslikeFramework::StaticClass()));

    if (SaveInstance)
    {
        SaveInstance->SetSavedData(DataToSave);
        CurrentSaveGameObject = SaveInstance;
        Data = DataToSave;

        // Async save
        UGameplayStatics::AsyncSaveGameToSlot(SaveInstance, CurrentSaveSlot, 0,
            FAsyncSaveGameToSlotDelegate::CreateLambda([this](const FString& SlotName, int32 UserIndex, bool bSuccess)
            {
                if (bSuccess)
                {
                    OnSaveComplete.Broadcast();
                }
            }));
    }
}

void UAC_SaveLoadManager::LoadData()
{
    TryPreloadData();
}

void UAC_SaveLoadManager::LoadDataAsync()
{
    if (CurrentSaveSlot.IsEmpty())
    {
        UpdateActiveSlot();
        if (CurrentSaveSlot.IsEmpty()) return;
    }

    if (UGameplayStatics::DoesSaveGameExist(CurrentSaveSlot, 0))
    {
        UGameplayStatics::AsyncLoadGameFromSlot(CurrentSaveSlot, 0,
            FAsyncLoadGameFromSlotDelegate::CreateUObject(this, &UAC_SaveLoadManager::OnAsyncLoadComplete));
    }
}

void UAC_SaveLoadManager::OnAsyncLoadComplete(const FString& SlotName, int32 UserIndex, USaveGame* LoadedSave)
{
    if (USG_SoulslikeFramework* SG = Cast<USG_SoulslikeFramework>(LoadedSave))
    {
        CurrentSaveGameObject = SG;
        Data = SG->GetSavedData();
        OnDataLoaded.Broadcast(Data);
    }
}

void UAC_SaveLoadManager::ShowSavingVisual()
{
    // This would typically show a saving indicator widget
    // Implementation depends on UI system
}

void UAC_SaveLoadManager::AddAndSaveSlots()
{
    // Add slot to game instance slot list and save
    UGameInstance* GI = UGameplayStatics::GetGameInstance(this);
    if (GI && GI->Implements<UBPI_GameInstance>())
    {
        // Implementation depends on BPI_GameInstance SaveSlotList function
    }
}

// ============================================================
// SERIALIZATION
// ============================================================

void UAC_SaveLoadManager::AddToSaveData(FGameplayTag SaveGameTag, const FInstancedStruct& DataToSave)
{
    // Add data to the save game entry map by tag
    // FSaveGameInfo needs a TMap<FGameplayTag, FInstancedStruct> property to store arbitrary data
    // Implementation pending struct update
}

bool UAC_SaveLoadManager::GetDataByTag(FGameplayTag SaveGameTag, FInstancedStruct& OutData)
{
    // Get data from the save game entry map by tag
    // This requires FSaveGameInfo to have a SaveGameEntry map
    // Returns true if found, false otherwise
    return false;
}

void UAC_SaveLoadManager::RefreshData()
{
    // Refresh the cached data from the save game object
    if (CurrentSaveGameObject)
    {
        Data = CurrentSaveGameObject->GetSavedData();
    }
}

bool UAC_SaveLoadManager::IsSaveDataValid() const
{
    // Check if the data is valid (e.g., has required fields set)
    return !Data.SlotName.IsEmpty();
}
