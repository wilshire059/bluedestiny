#include "W_Buff.h"

void UW_Buff::SetupBuff(FGameplayTag InBuffTag, UTexture2D* Icon, int32 StackCount, float Duration)
{
	BuffTag = InBuffTag;

	if (BuffIcon && Icon)
	{
		BuffIcon->SetBrushFromTexture(Icon);
	}

	UpdateStackCount(StackCount);
	UpdateDuration(Duration);
}

void UW_Buff::UpdateStackCount(int32 StackCount)
{
	if (StackCountText)
	{
		if (StackCount > 1)
		{
			StackCountText->SetText(FText::AsNumber(StackCount));
			StackCountText->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			StackCountText->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}

void UW_Buff::UpdateDuration(float RemainingDuration)
{
	if (DurationText)
	{
		if (RemainingDuration > 0.0f)
		{
			DurationText->SetText(FText::AsNumber(FMath::CeilToInt(RemainingDuration)));
			DurationText->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			DurationText->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}
