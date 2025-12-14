#include "W_Browser_Tooltip.h"

void UW_Browser_Tooltip::SetupTooltip(FText Title, FText Description, UTexture2D* Preview)
{
	if (TitleText)
	{
		TitleText->SetText(Title);
	}

	if (DescriptionText)
	{
		DescriptionText->SetText(Description);
	}

	if (PreviewImage)
	{
		if (Preview)
		{
			PreviewImage->SetBrushFromTexture(Preview);
			PreviewImage->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			PreviewImage->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}
