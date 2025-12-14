#include "W_Status.h"

void UW_Status::NativeConstruct()
{
    Super::NativeConstruct();

    // Bind OnVisibilityChanged via delegate?
    // UUserWidget::OnVisibilityChanged is an event provided for BPs. In C++ we override NativeOnVisibilityChanged.
    
    APawn* PlayerPawn = GetOwningPlayerPawn();
    if (PlayerPawn)
    {
        UAC_StatManager* LocalStatManager = PlayerPawn->FindComponentByClass<UAC_StatManager>();
        if (LocalStatManager)
        {
            LocalStatManager->OnLevelUpRequested.AddDynamic(this, &UW_Status::OnLevelUpdated);
            CurrentPlayerLevel = LocalStatManager->CurrentLevel; // Initial sync
        }
    }
}

/*
void UW_Status::NativeOnVisibilityChanged(ESlateVisibility InVisibility)
{
    Super::NativeOnVisibilityChanged(InVisibility);
    
    // Play Fade animation if Visible
    if (InVisibility == ESlateVisibility::Visible)
    {
        if (Fade)
        {
            PlayAnimationForward(Fade, 1.0f);
        }
    }
}
*/

void UW_Status::OnLevelUpdated(int32 Level)
{
    CurrentPlayerLevel = Level;
    // Update local TextBlock if exists? JSON showed binding to Variable "Level" in StatManager. 
    // Wait, StatBlock handles stats. W_Status might have a level text?
    // JSON analysis showed N17 VariableSet CurrentPlayerLevel.
    // It seems W_Status just stores it, maybe for binding in designer.
}
