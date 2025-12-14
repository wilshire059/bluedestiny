#include "W_Browser_Categories.h"

void UW_Browser_Categories::SetupCategories(const TArray<FText>& Categories)
{
	OnSetupCategories(Categories);
}

void UW_Browser_Categories::SelectCategory(int32 CategoryIndex)
{
	OnBrowserCategorySelected.Broadcast(CategoryIndex);
}
