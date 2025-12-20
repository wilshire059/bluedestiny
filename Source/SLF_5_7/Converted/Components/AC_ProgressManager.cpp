#include "AC_ProgressManager.h"

UAC_ProgressManager::UAC_ProgressManager()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UAC_ProgressManager::BeginPlay()
{
	Super::BeginPlay();

    // Initialize defaults if empty (or merge)
    for (const auto& Pair : DefaultsToProgress)
    {
        if (!ProgressState.Contains(Pair.Key))
        {
            ProgressState.Add(Pair.Key, Pair.Value);
        }
    }
}

void UAC_ProgressManager::SetProgress(FGameplayTag ID, E_Progress State)
{
    if (ID.IsValid())
    {
        ProgressState.Add(ID, State);
        OnProgressUpdated.Broadcast(ID, State);
    }
}

E_Progress UAC_ProgressManager::GetProgress(FGameplayTag ID) const
{
    if (ProgressState.Contains(ID))
    {
        return ProgressState[ID];
    }
    return E_Progress::NotStarted;
}

void UAC_ProgressManager::ExecuteGameplayEvents(const TArray<FDialogGameplayEvent>& GameplayEvents)
{
    // Process each gameplay event based on its EventTag
    for (const FDialogGameplayEvent& Event : GameplayEvents)
    {
        if (Event.EventTag.IsValid())
        {
            // Handle events based on tag (e.g., progress updates, item grants, etc.)
            // Full implementation would dispatch to appropriate handlers
        }
    }
}
