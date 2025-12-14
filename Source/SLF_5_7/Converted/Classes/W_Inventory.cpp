#include "W_Inventory.h"

void UW_Inventory::GridUp()
{
    // Logic placeholder
}

void UW_Inventory::GridDown()
{
    // Logic placeholder
}

void UW_Inventory::GridLeft()
{
    // Logic placeholder
}

void UW_Inventory::GridRight()
{
    // Logic placeholder
}

void UW_Inventory::NavigateCategories(bool bNext)
{
    if (!CanNavigate()) return;

    if (bNext)
    {
        CategoryNavigationIndex = FMath::Clamp(CategoryNavigationIndex + 1, 0, CategoryEntries.Num() - 1);
    }
    else
    {
        CategoryNavigationIndex = FMath::Clamp(CategoryNavigationIndex - 1, 0, CategoryEntries.Num() - 1);
    }
    
    // Call B_Update or dispatch event
}
