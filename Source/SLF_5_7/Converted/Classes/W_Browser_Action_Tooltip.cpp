#include "W_Browser_Action_Tooltip.h"

void UW_Browser_Action_Tooltip::SetupTooltip(FText ActionName, FText Description)
{
	if (ActionNameText)
	{
		ActionNameText->SetText(ActionName);
	}

	if (DescriptionText)
	{
		DescriptionText->SetText(Description);
	}
}
