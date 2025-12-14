#include "W_StatusEffectNotification.h"
#include "TimerManager.h"

void UW_StatusEffectNotification::ShowNotification(UTexture2D* Icon, FText EffectName)
{
	if (EffectIcon && Icon)
	{
		EffectIcon->SetBrushFromTexture(Icon);
	}

	if (EffectNameText)
	{
		EffectNameText->SetText(EffectName);
	}

	SetVisibility(ESlateVisibility::Visible);

	// Set timer to hide notification
	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().ClearTimer(HideTimerHandle);
		World->GetTimerManager().SetTimer(HideTimerHandle, this, &UW_StatusEffectNotification::HideNotification, DisplayDuration, false);
	}
}

void UW_StatusEffectNotification::HideNotification()
{
	// Play hide animation then remove
	RemoveFromParent();
}
