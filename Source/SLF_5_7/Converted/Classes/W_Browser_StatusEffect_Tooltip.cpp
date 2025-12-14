#include "W_Browser_StatusEffect_Tooltip.h"

void UW_Browser_StatusEffect_Tooltip::SetupTooltip(FText EffectName, FText Description)
{
	if (EffectNameText) EffectNameText->SetText(EffectName);
	if (DescriptionText) DescriptionText->SetText(Description);
}
