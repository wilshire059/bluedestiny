#include "SG_SaveSlots.h"

USG_SaveSlots::USG_SaveSlots()
{
}

void USG_SaveSlots::AddSlot(const FString& SlotName)
{
	if (!Slots.Contains(SlotName))
	{
		Slots.Add(SlotName);
	}
}

void USG_SaveSlots::RemoveSlot(const FString& SlotName)
{
	Slots.Remove(SlotName);
}

bool USG_SaveSlots::HasSlot(const FString& SlotName) const
{
	return Slots.Contains(SlotName);
}
