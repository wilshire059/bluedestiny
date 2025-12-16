#include "AC_AI_InteractionManager.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"
#include "Components/AC_ProgressManager.h"
#include "Components/AC_InventoryManager.h"
#include "DataAssets/PDA_Dialog.h"
#include "Engine/StreamableManager.h"
#include "Engine/AssetManager.h"
#include "Interfaces/BPI_Controller.h"

UAC_AI_InteractionManager::UAC_AI_InteractionManager()
{
    PrimaryComponentTick.bCanEverTick = false;
    CurrentIndex = 0;
    bDialogActive = false;
}

void UAC_AI_InteractionManager::BeginPlay()
{
    Super::BeginPlay();

    // Find ProgressManager on Owner if not set
    if (!ProgressManager)
    {
        if (AActor* Owner = GetOwner())
        {
            ProgressManager = Owner->FindComponentByClass<UAC_ProgressManager>();
        }
    }
}

// ============================================================
// DIALOG FUNCTIONS
// ============================================================

void UAC_AI_InteractionManager::BeginDialog(UAC_ProgressManager* InProgressManager, UUserWidget* InHUD)
{
    if (!DialogAsset)
    {
        return;
    }

    ProgressManager = InProgressManager;
    HUDWidget = InHUD;
    CurrentIndex = 0;
    bDialogActive = true;

    // Get dialog table based on progress
    TSoftObjectPtr<UDataTable> DialogTable = GetDialogTableBasedOnProgress(InProgressManager);

    if (DialogTable.IsNull())
    {
        return;
    }

    // Async load the dialog table
    if (!DialogTable.IsValid())
    {
        FStreamableManager& Streamable = UAssetManager::GetStreamableManager();
        Streamable.RequestAsyncLoad(
            DialogTable.ToSoftObjectPath(),
            FStreamableDelegate::CreateWeakLambda(this, [this, DialogTable]()
            {
                OnDialogTableLoaded(DialogTable);
            })
        );
    }
    else
    {
        OnDialogTableLoaded(DialogTable);
    }
}

void UAC_AI_InteractionManager::OnDialogTableLoaded(TSoftObjectPtr<UDataTable> LoadedTable)
{
    if (UDataTable* Table = LoadedTable.Get())
    {
        ActiveDialogTable = Table;
        DialogRows = Table->GetRowNames();

        OnDialogStarted.Broadcast(Table);
    }
}

void UAC_AI_InteractionManager::EndDialog()
{
    bDialogActive = false;
    CurrentIndex = 0;
    ActiveDialogTable = nullptr;
    DialogRows.Empty();

    OnDialogEnded.Broadcast();
}

void UAC_AI_InteractionManager::AdvanceDialog()
{
    if (!bDialogActive || !ActiveDialogTable)
    {
        return;
    }

    CurrentIndex++;

    if (CurrentIndex >= DialogRows.Num())
    {
        EndDialog();
    }
}

bool UAC_AI_InteractionManager::GetCurrentDialogEntry(UDataTable* DataTable, const TArray<FName>& Rows, FName& OutRowName)
{
    if (!DataTable || Rows.Num() == 0)
    {
        return false;
    }

    if (CurrentIndex < 0 || CurrentIndex >= Rows.Num())
    {
        return false;
    }

    OutRowName = Rows[CurrentIndex];
    return true;
}

bool UAC_AI_InteractionManager::IsDialogActive() const
{
    return bDialogActive;
}

// ============================================================
// PROGRESS FUNCTIONS
// ============================================================

void UAC_AI_InteractionManager::SetProgress(FGameplayTag ProgressTag, E_Progress State)
{
    UAC_ProgressManager* LocalProgressManager = GetLocalProgressManager();
    if (LocalProgressManager)
    {
        LocalProgressManager->SetProgress(ProgressTag, State);
    }
}

E_Progress UAC_AI_InteractionManager::GetProgress(FGameplayTag ProgressTag) const
{
    UAC_ProgressManager* LocalProgressManager = GetLocalProgressManager();
    if (LocalProgressManager)
    {
        return LocalProgressManager->GetProgress(ProgressTag);
    }
    return E_Progress::None;
}

UAC_ProgressManager* UAC_AI_InteractionManager::GetLocalProgressManager() const
{
    if (ProgressManager)
    {
        return ProgressManager;
    }

    // Try to find on owner
    if (AActor* Owner = GetOwner())
    {
        return Owner->FindComponentByClass<UAC_ProgressManager>();
    }

    return nullptr;
}

// ============================================================
// DIALOG TABLE FUNCTIONS
// ============================================================

TSoftObjectPtr<UDataTable> UAC_AI_InteractionManager::GetDialogTableBasedOnProgress(UAC_ProgressManager* InProgressManager)
{
    if (!DialogAsset)
    {
        return nullptr;
    }

    // Delegate to the dialog asset to determine which table to use
    return DialogAsset->GetDialogTableBasedOnProgress(InProgressManager);
}

// ============================================================
// GAMEPLAY EVENTS
// ============================================================

void UAC_AI_InteractionManager::ExecuteGameplayEvents(const TArray<FGameplayTag>& EventTags)
{
    // Execute each gameplay event tag
    for (const FGameplayTag& EventTag : EventTags)
    {
        // Would dispatch to a gameplay event system
        // This is typically handled by sending messages to the game mode or a global event dispatcher
    }
}

// ============================================================
// CURRENCY
// ============================================================

void UAC_AI_InteractionManager::AdjustCurrency(int32 Amount)
{
    // Find the player controller's inventory manager and adjust currency
    if (UWorld* World = GetWorld())
    {
        if (APlayerController* PC = World->GetFirstPlayerController())
        {
            if (PC->Implements<UBPI_Controller>())
            {
                if (UAC_InventoryManager* Inventory = IBPI_Controller::Execute_GetInventoryComponent(PC))
                {
                    Inventory->AdjustCurrency(Amount);
                }
            }
        }
    }
}
