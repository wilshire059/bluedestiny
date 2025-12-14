#include "W_LootNotification.h"
#include "TimerManager.h"

void UW_LootNotification::ShowLootNotification(UTexture2D* Icon, FText ItemName, int32 Quantity)
{
	if (ItemIcon && Icon)
	{
		ItemIcon->SetBrushFromTexture(Icon);
	}

	if (ItemNameText)
	{
		ItemNameText->SetText(ItemName);
	}

	if (QuantityText)
	{
		if (Quantity > 1)
		{
			QuantityText->SetText(FText::Format(NSLOCTEXT("Loot", "Quantity", "x{0}"), Quantity));
			QuantityText->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			QuantityText->SetVisibility(ESlateVisibility::Collapsed);
		}
	}

	SetVisibility(ESlateVisibility::Visible);

	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().ClearTimer(HideTimerHandle);
		World->GetTimerManager().SetTimer(HideTimerHandle, this, &UW_LootNotification::HideNotification, DisplayDuration, false);
	}
}

void UW_LootNotification::HideNotification()
{
	RemoveFromParent();
}
