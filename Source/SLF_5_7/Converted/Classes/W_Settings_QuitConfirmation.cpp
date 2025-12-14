#include "W_Settings_QuitConfirmation.h"
#include "Kismet/KismetSystemLibrary.h"

void UW_Settings_QuitConfirmation::NativeConstruct()
{
	Super::NativeConstruct();

	if (ConfirmButton)
	{
		ConfirmButton->OnClicked.AddDynamic(this, &UW_Settings_QuitConfirmation::HandleConfirmClicked);
	}

	if (CancelButton)
	{
		CancelButton->OnClicked.AddDynamic(this, &UW_Settings_QuitConfirmation::HandleCancelClicked);
	}
}

void UW_Settings_QuitConfirmation::HandleConfirmClicked()
{
	OnQuitConfirmed.Broadcast();
	UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, false);
}

void UW_Settings_QuitConfirmation::HandleCancelClicked()
{
	OnQuitCancelled.Broadcast();
	RemoveFromParent();
}
