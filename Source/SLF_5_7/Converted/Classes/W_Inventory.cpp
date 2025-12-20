#include "W_Inventory.h"

void UW_Inventory::GridUp()
{
    // Grid navigation handled by Blueprint widget's grid panel
    // This function is called by input binding and triggers Blueprint navigation
}

void UW_Inventory::GridDown()
{
    // Grid navigation handled by Blueprint widget's grid panel
}

void UW_Inventory::GridLeft()
{
    // Grid navigation handled by Blueprint widget's grid panel
}

void UW_Inventory::GridRight()
{
    // Grid navigation handled by Blueprint widget's grid panel
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
