#include "W_RestMenu_TimeEntry.h"

void UW_RestMenu_TimeEntry::NativeConstruct()
{
	Super::NativeConstruct();

	if (TimeButton)
	{
		TimeButton->OnClicked.AddDynamic(this, &UW_RestMenu_TimeEntry::HandleButtonClicked);
	}

	if (TimeText && !TimeLabel.IsEmpty())
	{
		TimeText->SetText(TimeLabel);
	}
}

void UW_RestMenu_TimeEntry::SetupTimeEntry(int32 InTimeIndex, FText InTimeLabel)
{
	TimeIndex = InTimeIndex;
	TimeLabel = InTimeLabel;

	if (TimeText)
	{
		TimeText->SetText(TimeLabel);
	}
}

void UW_RestMenu_TimeEntry::HandleButtonClicked()
{
	OnTimeEntrySelected.Broadcast(TimeIndex);
}
