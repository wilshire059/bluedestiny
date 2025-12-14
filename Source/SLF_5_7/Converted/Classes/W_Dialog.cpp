#include "W_Dialog.h"

void UW_Dialog::SetDialog(FText SpeakerName, FText Dialog, UTexture2D* Portrait)
{
	if (SpeakerNameText)
	{
		SpeakerNameText->SetText(SpeakerName);
	}

	if (DialogText)
	{
		DialogText->SetText(Dialog);
	}

	if (SpeakerPortrait && Portrait)
	{
		SpeakerPortrait->SetBrushFromTexture(Portrait);
		SpeakerPortrait->SetVisibility(ESlateVisibility::Visible);
	}
	else if (SpeakerPortrait)
	{
		SpeakerPortrait->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UW_Dialog::SetChoices(const TArray<FText>& Choices)
{
	// Implemented in Blueprint - creates choice buttons dynamically
}

void UW_Dialog::AdvanceDialog()
{
	OnDialogAdvanced.Broadcast();
}

void UW_Dialog::SelectChoice(int32 ChoiceIndex)
{
	OnDialogChoiceSelected.Broadcast(ChoiceIndex);
}

void UW_Dialog::CloseDialog()
{
	RemoveFromParent();
}
