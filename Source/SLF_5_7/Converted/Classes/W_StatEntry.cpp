#include "W_StatEntry.h"
#include "Internationalization/Text.h"

void UW_StatEntry::NativeConstruct()
{
    Super::NativeConstruct();

    if (ButtonIncrease)
    {
        ButtonIncrease->OnClicked.AddDynamic(this, &UW_StatEntry::OnIncreaseClicked);
        ButtonIncrease->SetVisibility(bShowAdjustButtons ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
    }

    if (ButtonDecrease)
    {
        ButtonDecrease->OnClicked.AddDynamic(this, &UW_StatEntry::OnDecreaseClicked);
        ButtonDecrease->SetVisibility(bShowAdjustButtons ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
    }

    if (Stat)
    {
        Stat->OnStatChanged.AddDynamic(this, &UW_StatEntry::OnStatUpdated);
        // Initial Update
        UpdateUI(Stat->CurrentValue, Stat->MaxValue);
        
        if (StatNameText)
        {
            StatNameText->SetText(FText::FromName(Stat->StatTag.GetTagName()));
        }
    }
}

void UW_StatEntry::OnStatUpdated(double NewValue, double MaxValue, double Percent)
{
    UpdateUI(NewValue, MaxValue);
}

void UW_StatEntry::UpdateUI(double NewValue, double MaxValue)
{
    if (StatValueText)
    {
        FString DebugString = FString::Printf(TEXT("%.0f / %.0f"), NewValue, MaxValue);
        StatValueText->SetText(FText::FromString(DebugString));
    }
}

void UW_StatEntry::OnIncreaseClicked()
{
    if (Stat)
    {
        Stat->ModifyStat(1.0f); // Adjust amount as needed
    }
}

void UW_StatEntry::OnDecreaseClicked()
{
    if (Stat)
    {
        Stat->ModifyStat(-1.0f);
    }
}
