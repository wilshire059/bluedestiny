#include "W_CategoryEntry.h"

void UW_CategoryEntry::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (CategoryNameText && !CategoryDisplayName.IsEmpty())
	{
		CategoryNameText->SetText(CategoryDisplayName);
	}
}

void UW_CategoryEntry::NativeConstruct()
{
	Super::NativeConstruct();

	if (CategoryButton)
	{
		CategoryButton->OnClicked.AddDynamic(this, &UW_CategoryEntry::HandleButtonClicked);
	}
}

void UW_CategoryEntry::HandleButtonClicked()
{
	OnCategoryEntrySelected.Broadcast(CategoryIndex);
}

void UW_CategoryEntry::SetSelected(bool bSelected)
{
	// Visual feedback - implemented in Blueprint
}
