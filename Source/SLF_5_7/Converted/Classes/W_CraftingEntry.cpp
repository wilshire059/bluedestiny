#include "W_CraftingEntry.h"

void UW_CraftingEntry::NativeConstruct()
{
	Super::NativeConstruct();

	if (EntryButton)
	{
		EntryButton->OnClicked.AddDynamic(this, &UW_CraftingEntry::HandleEntryClicked);
	}
}

void UW_CraftingEntry::SetupEntry(int32 InEntryIndex, const FCraftingInfo& CraftingInfo)
{
	EntryIndex = InEntryIndex;

	// Item name and icon would be set from the associated item asset
	// FCraftingInfo contains RequiredItems and bCanBeCrafted
}

void UW_CraftingEntry::HandleEntryClicked()
{
	OnCraftingEntrySelected.Broadcast(EntryIndex);
}

void UW_CraftingEntry::SetSelected(bool bSelected)
{
	// Visual feedback for selection - implemented in Blueprint
}
