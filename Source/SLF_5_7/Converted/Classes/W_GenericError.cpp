#include "W_GenericError.h"

void UW_GenericError::NativeConstruct()
{
	Super::NativeConstruct();

	if (OkButton)
	{
		OkButton->OnClicked.AddDynamic(this, &UW_GenericError::HandleOkClicked);
	}
}

void UW_GenericError::ShowError(FText Title, FText Message)
{
	if (TitleText)
	{
		TitleText->SetText(Title);
	}

	if (MessageText)
	{
		MessageText->SetText(Message);
	}

	SetVisibility(ESlateVisibility::Visible);
}

void UW_GenericError::HandleOkClicked()
{
	RemoveFromParent();
}
