#include "W_Settings_CenteredText.h"

void UW_Settings_CenteredText::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (CenteredText && !DisplayText.IsEmpty())
	{
		CenteredText->SetText(DisplayText);
	}
}

void UW_Settings_CenteredText::SetText(FText NewText)
{
	DisplayText = NewText;
	if (CenteredText)
	{
		CenteredText->SetText(NewText);
	}
}
