#include "W_FirstLootNotification.h"
#include "TimerManager.h"

void UW_FirstLootNotification::ShowFirstLootNotification(UTexture2D* Icon, FText ItemName)
{
	if (ItemIcon && Icon)
	{
		ItemIcon->SetBrushFromTexture(Icon);
	}

	if (ItemNameText)
	{
		ItemNameText->SetText(ItemName);
	}

	SetVisibility(ESlateVisibility::Visible);

	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().ClearTimer(HideTimerHandle);
		World->GetTimerManager().SetTimer(HideTimerHandle, this, &UW_FirstLootNotification::HideNotification, DisplayDuration, false);
	}
}

void UW_FirstLootNotification::HideNotification()
{
	RemoveFromParent();
}
