#include "W_Settings_KeyMapping_Category.h"

void UW_Settings_KeyMapping_Category::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (CategoryNameText && !CategoryDisplayName.IsEmpty())
	{
		CategoryNameText->SetText(CategoryDisplayName);
	}
}

void UW_Settings_KeyMapping_Category::SetupCategory(FText InCategoryName)
{
	CategoryDisplayName = InCategoryName;

	if (CategoryNameText)
	{
		CategoryNameText->SetText(CategoryDisplayName);
	}
}
