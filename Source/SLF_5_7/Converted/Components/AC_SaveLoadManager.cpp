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

    UpdateActiveSlot(); // Sync slot name
    TryPreloadData();   // Auto-load on begin play if desired
}

void UAC_SaveLoadManager::UpdateActiveSlot()
{
    UGameInstance* GI = UGameplayStatics::GetGameInstance(this);
    if (GI && GI->Implements<UBPI_GameInstance>())
    {
        IBPI_GameInstance::Execute_GetActiveSlotName(GI, CurrentSaveSlot);
    }
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
            OnDataLoaded.Broadcast(SG->GetSavedData());
        }
    }
}

void UAC_SaveLoadManager::SaveData(const FSaveGameInfo& DataToSave)
{
    if (CurrentSaveSlot.IsEmpty())
    {
        // Try fallback or error
        UpdateActiveSlot();
        if (CurrentSaveSlot.IsEmpty()) return;
    }

    USG_SoulslikeFramework* SaveInstance = Cast<USG_SoulslikeFramework>(UGameplayStatics::CreateSaveGameObject(USG_SoulslikeFramework::StaticClass()));
    if (SaveInstance)
    {
        SaveInstance->SetSavedData(DataToSave);
        UGameplayStatics::SaveGameToSlot(SaveInstance, CurrentSaveSlot, 0);
    }
}

void UAC_SaveLoadManager::LoadData()
{
    TryPreloadData(); // Re-use manual load logic
}
