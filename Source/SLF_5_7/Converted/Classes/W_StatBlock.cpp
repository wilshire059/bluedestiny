#include "W_StatBlock.h"
#include "Components/AC_StatManager.h"
#include "Classes/B_Stat.h"
#include "W_StatEntry.h"
#include "Blueprint/WidgetTree.h" // For CreateWidget? Or just standard hierarchy

void UW_StatBlock::NativePreConstruct()
{
    Super::NativePreConstruct();
    // Logic for design time (IsDesignTime)
}

void UW_StatBlock::NativeConstruct()
{
    Super::NativeConstruct();

    APawn* PlayerPawn = GetOwningPlayerPawn();
    if (PlayerPawn)
    {
        UAC_StatManager* LocalStatManager = PlayerPawn->FindComponentByClass<UAC_StatManager>();
        if (LocalStatManager)
        {
            LocalStatManager->OnStatsInitialized.AddDynamic(this, &UW_StatBlock::OnStatsInitialized);
            SetupCurrentStats(); // Try setup immediately
        }
    }
}

void UW_StatBlock::OnStatsInitialized()
{
    SetupCurrentStats();
}

void UW_StatBlock::SetupCurrentStats()
{
    if (!StatBox) return;

    StatBox->ClearChildren();

    APawn* PlayerPawn = GetOwningPlayerPawn();
    if (!PlayerPawn) return;

    UAC_StatManager* LocalStatManager = PlayerPawn->FindComponentByClass<UAC_StatManager>();
    if (!LocalStatManager) return;

    // Use GetAllStats if available in C++ API of StatManager
    // Assuming StatManager has a function or map
    // If StatManager was migrated, check its API.
    // Usually it has a TMap or TArray of stats.

    // Iterate over Stats map directly
    for (auto& Elem : LocalStatManager->Stats)
    {
        UB_Stat* Stat = Elem.Value;
        if (Stat)
        {
            UW_StatEntry* EntryWidget = CreateWidget<UW_StatEntry>(this, UW_StatEntry::StaticClass());
            if (EntryWidget)
            {
                EntryWidget->Stat = Stat;
                EntryWidget->bShowAdjustButtons = bShowUpgradeButtons;
                EntryWidget->UpdateUI(Stat->CurrentValue, Stat->MaxValue); 
                StatBox->AddChildToVerticalBox(EntryWidget);
            }
        }
    }
}
