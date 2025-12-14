#include "W_StatusEffectBar.h"
#include "W_Buff.h"

void UW_StatusEffectBar::AddStatusEffect(FGameplayTag EffectTag, UTexture2D* Icon, int32 StackCount, float Duration, bool bIsDebuff)
{
	// Implemented in Blueprint - creates buff widget and adds to appropriate container
}

void UW_StatusEffectBar::UpdateStatusEffect(FGameplayTag EffectTag, int32 StackCount, float Duration)
{
	if (UW_Buff** FoundWidget = ActiveBuffWidgets.Find(EffectTag))
	{
		if (*FoundWidget)
		{
			(*FoundWidget)->UpdateStackCount(StackCount);
			(*FoundWidget)->UpdateDuration(Duration);
		}
	}
}

void UW_StatusEffectBar::RemoveStatusEffect(FGameplayTag EffectTag)
{
	if (UW_Buff** FoundWidget = ActiveBuffWidgets.Find(EffectTag))
	{
		if (*FoundWidget)
		{
			(*FoundWidget)->RemoveFromParent();
		}
		ActiveBuffWidgets.Remove(EffectTag);
	}
}

void UW_StatusEffectBar::ClearAllEffects()
{
	for (auto& Pair : ActiveBuffWidgets)
	{
		if (Pair.Value)
		{
			Pair.Value->RemoveFromParent();
		}
	}
	ActiveBuffWidgets.Empty();
}
