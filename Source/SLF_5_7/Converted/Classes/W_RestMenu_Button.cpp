#include "W_RestMenu_Button.h"

void UW_RestMenu_Button::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (ButtonText && !ButtonLabel.IsEmpty())
	{
		ButtonText->SetText(ButtonLabel);
	}
}

void UW_RestMenu_Button::NativeConstruct()
{
	Super::NativeConstruct();

	if (RestButton)
	{
		RestButton->OnClicked.AddDynamic(this, &UW_RestMenu_Button::HandleButtonClicked);
	}
}

void UW_RestMenu_Button::HandleButtonClicked()
{
	OnRestButtonClicked.Broadcast(ButtonIndex);
}
