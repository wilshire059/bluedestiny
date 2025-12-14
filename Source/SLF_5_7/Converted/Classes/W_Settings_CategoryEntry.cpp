#include "W_Settings_CategoryEntry.h"

void UW_Settings_CategoryEntry::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (CategoryNameText && !CategoryDisplayName.IsEmpty())
	{
		CategoryNameText->SetText(CategoryDisplayName);
	}
}

void UW_Settings_CategoryEntry::NativeConstruct()
{
	Super::NativeConstruct();

	if (CategoryButton)
	{
		CategoryButton->OnClicked.AddDynamic(this, &UW_Settings_CategoryEntry::HandleButtonClicked);
	}
}

void UW_Settings_CategoryEntry::HandleButtonClicked()
{
	OnSettingsCategorySelected.Broadcast(CategoryIndex);
}

void UW_Settings_CategoryEntry::SetSelected(bool bSelected)
{
	// Visual feedback for selected state - implemented in Blueprint
}
