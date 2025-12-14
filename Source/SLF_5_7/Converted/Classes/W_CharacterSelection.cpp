#include "W_CharacterSelection.h"

void UW_CharacterSelection::NativeConstruct()
{
	Super::NativeConstruct();
	OnSetupCharacters();
}

void UW_CharacterSelection::SelectCharacter(int32 CharacterIndex)
{
	SelectedCharacterIndex = CharacterIndex;
}

void UW_CharacterSelection::ConfirmSelection()
{
	OnCharacterSelected.Broadcast(SelectedCharacterIndex);
}
