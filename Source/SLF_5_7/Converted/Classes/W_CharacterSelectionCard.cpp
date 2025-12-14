#include "W_CharacterSelectionCard.h"

void UW_CharacterSelectionCard::NativeConstruct()
{
	Super::NativeConstruct();

	if (CardButton)
	{
		CardButton->OnClicked.AddDynamic(this, &UW_CharacterSelectionCard::HandleCardClicked);
	}
}

void UW_CharacterSelectionCard::HandleCardClicked()
{
	OnCharacterCardSelected.Broadcast(CardIndex);
}

void UW_CharacterSelectionCard::SetSelected(bool bSelected)
{
	// Visual feedback for selection - implemented in Blueprint
}
