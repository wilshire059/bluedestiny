#include "W_Error.h"

void UW_Error::NativeConstruct()
{
	Super::NativeConstruct();

	if (DismissButton)
	{
		DismissButton->OnClicked.AddDynamic(this, &UW_Error::HandleDismissClicked);
	}
}

void UW_Error::ShowError(FText ErrorMessage)
{
	if (ErrorText)
	{
		ErrorText->SetText(ErrorMessage);
	}

	SetVisibility(ESlateVisibility::Visible);
}

void UW_Error::HandleDismissClicked()
{
	OnErrorDismissed.Broadcast();
	RemoveFromParent();
}
