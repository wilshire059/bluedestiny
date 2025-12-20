#include "SG_SaveSlots.h"

USG_SaveSlots::USG_SaveSlots()
{
}

void USG_SaveSlots::AddSlot(const FString& SlotName)
{
	// Check if slot already exists - if not in the array, add it
	if (!Slots.Contains(SlotName))
	{
		Slots.AddUnique(SlotName);
	}
	// Always update LastSavedSlot to the slot being added/accessed
	LastSavedSlot = SlotName;
}

void USG_SaveSlots::RemoveSlot(const FString& SlotName)
{
	Slots.Remove(SlotName);
}

bool USG_SaveSlots::HasSlot(const FString& SlotName) const
{
	return Slots.Contains(SlotName);
}
