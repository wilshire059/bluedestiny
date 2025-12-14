#include "W_TargetExecutionIndicator.h"

void UW_TargetExecutionIndicator::ShowIndicator_Implementation(AActor* TargetActor)
{
	// Determine if execution is available based on target
	bool bCanExecute = TargetActor != nullptr;
	SetCanExecute(bCanExecute);
	SetVisibility(ESlateVisibility::Visible);
}

void UW_TargetExecutionIndicator::HideIndicator_Implementation()
{
	SetVisibility(ESlateVisibility::Collapsed);
}

void UW_TargetExecutionIndicator::SetCanExecute(bool bCanExecute)
{
	if (ExecutionIcon)
	{
		UTexture2D* Icon = bCanExecute ? ExecuteAvailableIcon : ExecuteUnavailableIcon;
		if (Icon)
		{
			ExecutionIcon->SetBrushFromTexture(Icon);
		}
	}
}
