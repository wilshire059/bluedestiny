#include "AC_AI_InteractionManager.h"
// #include "W_HUD.h" // Widget logic usually handled in UI layer

UAC_AI_InteractionManager::UAC_AI_InteractionManager()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UAC_AI_InteractionManager::BeginPlay()
{
	Super::BeginPlay();
    
    // Find ProgressManager on Owner if not set
    if (!ProgressManager)
    {
        ProgressManager = GetOwner()->FindComponentByClass<UAC_ProgressManager>();
    }
}

void UAC_AI_InteractionManager::BeginDialog()
{
    if (DialogAsset && ProgressManager)
    {
        // TSoftObjectPtr<UDataTable> Table = DialogAsset->GetDialogTableBasedOnProgress(ProgressManager);
        // For now assuming direct call or simplified
        // if (UDataTable* LoadedTable = Table.LoadSynchronous())
        // {
        //     OnDialogStarted.Broadcast(LoadedTable);
        // }
    }
}
