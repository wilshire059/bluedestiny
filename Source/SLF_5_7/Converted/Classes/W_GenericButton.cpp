#include "W_GenericButton.h"

void UW_GenericButton::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (ButtonText && !ButtonLabel.IsEmpty())
	{
		ButtonText->SetText(ButtonLabel);
	}
}

void UW_GenericButton::NativeConstruct()
{
	Super::NativeConstruct();

	if (GenericButton)
	{
		GenericButton->OnClicked.AddDynamic(this, &UW_GenericButton::HandleButtonClicked);
	}
}

void UW_GenericButton::HandleButtonClicked()
{
	OnGenericButtonClicked.Broadcast(ButtonID);
}

void UW_GenericButton::SetButtonLabel(FText NewLabel)
{
	ButtonLabel = NewLabel;
	if (ButtonText)
	{
		ButtonText->SetText(NewLabel);
	}
}

void UW_GenericButton::SetButtonEnabled(bool bEnabled)
{
	if (GenericButton)
	{
		GenericButton->SetIsEnabled(bEnabled);
	}
}
