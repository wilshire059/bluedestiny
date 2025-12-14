#include "W_Interaction.h"

void UW_Interaction::ShowInteraction(FText ActionText, FText ItemName)
{
	if (InteractionText)
	{
		InteractionText->SetText(ActionText);
	}

	if (ItemNameText)
	{
		if (!ItemName.IsEmpty())
		{
			ItemNameText->SetText(ItemName);
			ItemNameText->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			ItemNameText->SetVisibility(ESlateVisibility::Collapsed);
		}
	}

	SetVisibility(ESlateVisibility::Visible);
}

void UW_Interaction::HideInteraction()
{
	SetVisibility(ESlateVisibility::Collapsed);
}

void UW_Interaction::SetInteractionKey(FKey Key)
{
	// Key icon would be set based on input type (keyboard/gamepad)
	// Implemented in Blueprint for visual customization
}
