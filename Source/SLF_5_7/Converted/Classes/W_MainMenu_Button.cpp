#include "W_MainMenu_Button.h"

void UW_MainMenu_Button::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (ButtonText && !ButtonLabel.IsEmpty())
	{
		ButtonText->SetText(ButtonLabel);
	}
}

void UW_MainMenu_Button::NativeConstruct()
{
	Super::NativeConstruct();

	if (MenuButton)
	{
		MenuButton->OnClicked.AddDynamic(this, &UW_MainMenu_Button::HandleButtonClicked);
		MenuButton->SetIsEnabled(bButtonEnabled);
	}
}

void UW_MainMenu_Button::HandleButtonClicked()
{
	OnMainMenuButtonClicked.Broadcast(ButtonIndex);
}

void UW_MainMenu_Button::SetButtonEnabled(bool bEnabled)
{
	bButtonEnabled = bEnabled;
	if (MenuButton)
	{
		MenuButton->SetIsEnabled(bEnabled);
	}
}
