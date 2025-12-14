#include "W_Browser_AnimsetTooltip.h"

void UW_Browser_AnimsetTooltip::SetupTooltip(FText AnimsetName, const TArray<FText>& Owners)
{
	if (AnimsetNameText)
	{
		AnimsetNameText->SetText(AnimsetName);
	}
	OnSetupOwners(Owners);
}
