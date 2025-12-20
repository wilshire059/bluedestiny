#include "AC_AI_InteractionManager.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Components/AC_ProgressManager.h"
#include "Components/AC_InventoryManager.h"
#include "DataAssets/PDA_Dialog.h"
#include "DataAssets/PDA_Vendor.h"
#include "Classes/W_HUD.h"
#include "Engine/StreamableManager.h"
#include "Engine/AssetManager.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/DataTable.h"

UAC_AI_InteractionManager::UAC_AI_InteractionManager()
{
    PrimaryComponentTick.bCanEverTick = false;

    // Initialize properties with default values from Blueprint CDO
    CurrentIndex = 0;
    MaxIndex = 0;
    Name = FText::FromString("Npc Name"); // Default from classDefaults
}

void UAC_AI_InteractionManager::BeginPlay()
{
    Super::BeginPlay();
}

// ============================================================
// CUSTOM EVENTS (BlueprintCallable)
// ============================================================

void UAC_AI_InteractionManager::Event_BeginDialog(UAC_ProgressManager* InProgressManager, UW_HUD* HUD)
{
    // Validate DialogAsset
    if (!DialogAsset)
    {
        return;
    }

    // Store ProgressManager
    ProgressManager = InProgressManager;

    // Get dialog table based on progress
    TSoftObjectPtr<UDataTable> DialogTable = DialogAsset->GetDialogTableBasedOnProgress(InProgressManager);

    // Check if ActiveTable is different from new table
    if (ActiveTable != DialogTable)
    {
        // Reset CurrentIndex if changing tables
        CurrentIndex = 0;
    }

    // Store the new ActiveTable
    ActiveTable = DialogTable;

    // Async load the dialog table
    if (!ActiveTable.IsNull())
    {
        FStreamableManager& Streamable = UAssetManager::GetStreamableManager();
        Streamable.RequestAsyncLoad(
            ActiveTable.ToSoftObjectPath(),
            FStreamableDelegate::CreateWeakLambda(this, [this, InProgressManager, HUD]()
            {
                OnDialogTableLoadedForBeginDialog(ActiveTable, InProgressManager, HUD);
            })
        );
    }
}

void UAC_AI_InteractionManager::OnDialogTableLoadedForBeginDialog(
    TSoftObjectPtr<UDataTable> LoadedTable,
    UAC_ProgressManager* InProgressManager,
    UW_HUD* HUD)
{
    UDataTable* Table = Cast<UDataTable>(LoadedTable.Get());
    if (!Table || !HUD)
    {
        return;
    }

    // Get all row names from the loaded table
    TArray<FName> Rows = Table->GetRowNames();

    // Get the current dialog entry
    FDialogEntry DialogEntry;
    GetCurrentDialogEntry(Table, Rows, DialogEntry);

    // Calculate MaxIndex (array length - 1)
    MaxIndex = FMath::Max(0, Rows.Num() - 1);

    // Execute gameplay events from the dialog entry
    if (InProgressManager && DialogEntry.GameplayEvents.Num() > 0)
    {
        InProgressManager->ExecuteGameplayEvents(DialogEntry.GameplayEvents);
    }

    // Clamp CurrentIndex to valid range [0, MaxIndex]
    int32 NewIndex = CurrentIndex + 1;
    CurrentIndex = FMath::Clamp(NewIndex, 0, MaxIndex);

    // Check if we've reached the last entry (before increment)
    int32 CheckIndex = CurrentIndex - 2; // CurrentIndex was already incremented, so check original value
    if (CheckIndex == MaxIndex)
    {
        // Call OnDialogFinished delegate
        OnDialogFinished.Broadcast();

        // Check for vendor asset
        if (VendorAsset)
        {
            // Setup NPC window with vendor
            HUD->Event_SetupNpcWindow(Name, VendorAsset, this);
        }
        else
        {
            // Finish dialog without vendor
            HUD->Event_FinishDialog();
        }
    }
    else
    {
        // Setup dialog with current entry text
        HUD->Event_SetupDialog(DialogEntry.Entry);
    }
}

void UAC_AI_InteractionManager::Event_AdjustIndexForExit()
{
    // Validate ActiveTable
    if (ActiveTable.IsNull())
    {
        return;
    }

    // Async load the table
    FStreamableManager& Streamable = UAssetManager::GetStreamableManager();
    Streamable.RequestAsyncLoad(
        ActiveTable.ToSoftObjectPath(),
        FStreamableDelegate::CreateWeakLambda(this, [this]()
        {
            OnDialogTableLoadedForAdjustIndex(ActiveTable);
        })
    );
}

void UAC_AI_InteractionManager::OnDialogTableLoadedForAdjustIndex(TSoftObjectPtr<UDataTable> LoadedTable)
{
    UDataTable* Table = Cast<UDataTable>(LoadedTable.Get());
    if (!Table)
    {
        return;
    }

    // Get all row names
    TArray<FName> Rows = Table->GetRowNames();

    // Check if CurrentIndex equals array length
    if (CurrentIndex == Rows.Num())
    {
        // Adjust index down by 1
        CurrentIndex = CurrentIndex - 1;
    }
}

void UAC_AI_InteractionManager::Event_ResetDialogIndex()
{
    // Validate DialogAsset
    if (!DialogAsset)
    {
        return;
    }

    // Reset CurrentIndex to 0
    CurrentIndex = 0;
}

// ============================================================
// DIALOG FUNCTIONS
// ============================================================

void UAC_AI_InteractionManager::GetCurrentDialogEntry(
    UDataTable* DataTable,
    const TArray<FName>& Rows,
    FDialogEntry& OutRow)
{
    if (!DataTable || Rows.Num() == 0)
    {
        OutRow = FDialogEntry();
        return;
    }

    // Ensure CurrentIndex is valid
    if (CurrentIndex < 0 || CurrentIndex >= Rows.Num())
    {
        OutRow = FDialogEntry();
        return;
    }

    // Get the row name at CurrentIndex
    FName RowName = Rows[CurrentIndex];

    // Get the data table row
    FDialogEntry* RowData = DataTable->FindRow<FDialogEntry>(RowName, TEXT("GetCurrentDialogEntry"));
    if (RowData)
    {
        OutRow = *RowData;
    }
    else
    {
        OutRow = FDialogEntry();
    }
}
