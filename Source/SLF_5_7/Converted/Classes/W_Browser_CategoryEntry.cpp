#include "W_Browser_CategoryEntry.h"

void UW_Browser_CategoryEntry::NativeConstruct()
{
	Super::NativeConstruct();

	if (CategoryButton)
	{
		CategoryButton->OnClicked.AddDynamic(this, &UW_Browser_CategoryEntry::HandleCategoryClicked);
	}
}

void UW_Browser_CategoryEntry::SetupEntry(int32 InCategoryIndex, FText InCategoryDisplayName)
{
	CategoryIndex = InCategoryIndex;

	if (CategoryNameText)
	{
		CategoryNameText->SetText(InCategoryDisplayName);
	}
}

void UW_Browser_CategoryEntry::HandleCategoryClicked()
{
	OnBrowserCategoryEntrySelected.Broadcast(CategoryIndex);
}

void UW_Browser_CategoryEntry::SetSelected(bool bSelected)
{
	// Visual feedback - implemented in Blueprint
}
