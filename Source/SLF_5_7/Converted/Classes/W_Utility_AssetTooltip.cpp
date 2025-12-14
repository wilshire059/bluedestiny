#include "W_Utility_AssetTooltip.h"

void UW_Utility_AssetTooltip::SetupTooltip(UObject* Asset)
{
	if (!Asset)
	{
		return;
	}

	if (AssetNameText)
	{
		AssetNameText->SetText(FText::FromString(Asset->GetName()));
	}

	if (AssetPathText)
	{
		AssetPathText->SetText(FText::FromString(Asset->GetPathName()));
	}

	OnSetupProperties(Asset);
}
