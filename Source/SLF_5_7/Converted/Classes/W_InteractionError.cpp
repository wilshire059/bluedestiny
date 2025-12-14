#include "W_InteractionError.h"
#include "TimerManager.h"

void UW_InteractionError::ShowInteractionError(FText ErrorMessage)
{
	if (ErrorText)
	{
		ErrorText->SetText(ErrorMessage);
	}

	SetVisibility(ESlateVisibility::Visible);

	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().ClearTimer(HideTimerHandle);
		World->GetTimerManager().SetTimer(HideTimerHandle, this, &UW_InteractionError::HideError, DisplayDuration, false);
	}
}

void UW_InteractionError::HideError()
{
	SetVisibility(ESlateVisibility::Collapsed);
}
