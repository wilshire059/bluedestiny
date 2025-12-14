#include "W_GameMenu.h"

/*
void UW_GameMenu::NativeOnVisibilityChanged(ESlateVisibility InVisibility)
{
    Super::NativeOnVisibilityChanged(InVisibility);
}
*/

void UW_GameMenu::OnMenuButtonSelected(UW_GameMenu_Button* SelectedButton, bool bSelected)
{
    if (!SelectedButton) return;

    // Deselect others
    for (UW_GameMenu_Button* Btn : MenuButtons)
    {
        if (Btn && Btn != SelectedButton)
        {
            Btn->SetGameMenuButtonSelected(false);
        }
    }

    SelectedButton->SetGameMenuButtonSelected(true);
    OnGameMenuWidgetRequest.Broadcast(SelectedButton->WidgetTag);
}
