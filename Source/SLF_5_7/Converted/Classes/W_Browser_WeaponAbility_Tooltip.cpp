#include "W_Browser_WeaponAbility_Tooltip.h"

void UW_Browser_WeaponAbility_Tooltip::SetupTooltip(FText AbilityName, FText Description)
{
	if (AbilityNameText) AbilityNameText->SetText(AbilityName);
	if (DescriptionText) DescriptionText->SetText(Description);
}
