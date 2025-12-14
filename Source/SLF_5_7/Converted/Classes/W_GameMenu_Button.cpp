#include "W_GameMenu_Button.h"

void UW_GameMenu_Button::NativeConstruct()
{
    Super::NativeConstruct();
    if (Button)
    {
        Button->OnClicked.AddDynamic(this, &UW_GameMenu_Button::OnButtonClicked);
    }
}

void UW_GameMenu_Button::OnButtonClicked()
{
    OnSelected.Broadcast(this, true); // Simplified logic
}

void UW_GameMenu_Button::SetGameMenuButtonSelected(bool bSelected)
{
    // Update visual state (e.g., color)
    if (Button)
    {
       // Set style or color.. simplified
        if (bSelected)
        {
            Button->SetBackgroundColor(FLinearColor::Green);
        }
        else
        {
            Button->SetBackgroundColor(FLinearColor::White);
        }
    }
}
