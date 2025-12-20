#include "W_TargetExecutionIndicator.h"
#include "Animation/WidgetAnimation.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

void UW_TargetExecutionIndicator::ToggleExecutionIcon_Implementation(bool bVisible)
{
	if (bVisible)
	{
		// Show the icon and play fade animation
		if (ExecuteLockIcon)
		{
			ExecuteLockIcon->SetVisibility(ESlateVisibility::Visible);
		}

		if (FadeExecuteIcon)
		{
			PlayAnimation(FadeExecuteIcon);
		}
	}
	else
	{
		// Hide the icon
		if (ExecuteLockIcon)
		{
			ExecuteLockIcon->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}

void UW_TargetExecutionIndicator::SetCanExecute(bool bCanExecute)
{
	if (ExecuteLockIcon)
	{
		UTexture2D* Icon = bCanExecute ? ExecuteAvailableIcon : ExecuteUnavailableIcon;
		if (Icon)
		{
			ExecuteLockIcon->SetBrushFromTexture(Icon);
		}
	}
}
