#include "W_LoadGame_Entry.h"

void UW_LoadGame_Entry::NativeConstruct()
{
	Super::NativeConstruct();

	if (LoadButton)
	{
		LoadButton->OnClicked.AddDynamic(this, &UW_LoadGame_Entry::HandleLoadClicked);
	}

	if (DeleteButton)
	{
		DeleteButton->OnClicked.AddDynamic(this, &UW_LoadGame_Entry::HandleDeleteClicked);
	}
}

void UW_LoadGame_Entry::SetupEntry(int32 InSlotIndex, const FSaveGameInfo& SaveInfo)
{
	SlotIndex = InSlotIndex;

	if (SlotNameText)
	{
		SlotNameText->SetText(FText::FromString(SaveInfo.SlotName));
	}

	if (PlayTimeText)
	{
		// Format play time from total seconds
		int32 Hours = SaveInfo.TotalPlayTime / 3600;
		int32 Minutes = (SaveInfo.TotalPlayTime % 3600) / 60;
		FText TimeText = FText::Format(NSLOCTEXT("SaveGame", "PlayTime", "{0}h {1}m"), Hours, Minutes);
		PlayTimeText->SetText(TimeText);
	}

	if (LocationText)
	{
		// LastLocation is a GameplayTag
		LocationText->SetText(FText::FromString(SaveInfo.LastLocation.ToString()));
	}
}

void UW_LoadGame_Entry::HandleLoadClicked()
{
	OnLoadEntrySelected.Broadcast(SlotIndex);
}

void UW_LoadGame_Entry::HandleDeleteClicked()
{
	OnLoadEntryDeleteRequested.Broadcast(SlotIndex);
}
