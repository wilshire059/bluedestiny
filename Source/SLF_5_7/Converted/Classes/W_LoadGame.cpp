#include "W_LoadGame.h"

void UW_LoadGame::SetupSaveSlots(const TArray<FSaveGameInfo>& SaveSlots)
{
	OnSetupSaveSlots(SaveSlots);
}

void UW_LoadGame::SelectSlot(int32 SlotIndex)
{
	OnSaveSlotSelected.Broadcast(SlotIndex);
}

void UW_LoadGame::DeleteSlot(int32 SlotIndex)
{
	// Implemented in Blueprint - should show confirmation dialog
}

void UW_LoadGame::CloseMenu()
{
	RemoveFromParent();
}
