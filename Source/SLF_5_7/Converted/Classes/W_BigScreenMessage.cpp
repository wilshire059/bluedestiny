#include "W_BigScreenMessage.h"

void UW_BigScreenMessage::ShowMessage(FText InMessage, UMaterialInterface* GradientMaterial, bool bHasBackdrop, float AnimationRateScale)
{
	if (Message)
	{
		Message->SetText(InMessage);
	}

	if (GradientImage && GradientMaterial)
	{
		GradientImage->SetBrushFromMaterial(GradientMaterial);
	}

	if (Backdrop)
	{
		Backdrop->SetVisibility(bHasBackdrop ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
	}

	// Play show animation - implemented in Blueprint
	SetVisibility(ESlateVisibility::Visible);
}

void UW_BigScreenMessage::HideMessage()
{
	// Play hide animation - implemented in Blueprint
	SetVisibility(ESlateVisibility::Collapsed);
}
