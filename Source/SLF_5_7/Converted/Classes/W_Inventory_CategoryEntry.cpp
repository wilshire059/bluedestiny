#include "W_Inventory_CategoryEntry.h"
#include "Components/Button.h"
#include "Styling/SlateColor.h"

void UW_Inventory_CategoryEntry::NativeConstruct()
{
	Super::NativeConstruct();

	if (Button)
	{
		Button->OnClicked.AddDynamic(this, &UW_Inventory_CategoryEntry::OnButtonClicked);
		Button->OnHovered.AddDynamic(this, &UW_Inventory_CategoryEntry::OnButtonHovered);
		Button->OnUnhovered.AddDynamic(this, &UW_Inventory_CategoryEntry::OnButtonUnhovered);
	}

	// Set Icon if valid
    if (!InventoryCategoryData.CategoryIcon.IsNull())
    {
        // Simple synchronous load or async load could be used. JSON used SetBrushFromSoftTexture
        CategoryIconImage->SetBrushFromSoftTexture(InventoryCategoryData.CategoryIcon);
    }
}

void UW_Inventory_CategoryEntry::SetInventoryCategorySelected(bool bSelected)
{
	bIsSelected = bSelected;
	// Logic to change color or opacity based on selection
    if (CategoryIconImage)
    {
        // Example logic from JSON: SetBrushTintColor based on selection
        FLinearColor Color = bSelected ? FLinearColor(0.85f, 0.74f, 0.62f, 1.0f) : FLinearColor(0.49f, 0.39f, 0.28f, 1.0f);
        CategoryIconImage->SetBrushTintColor(FSlateColor(Color));
    }
}

void UW_Inventory_CategoryEntry::OnButtonClicked()
{
	SetInventoryCategorySelected(true);
	OnCategorySelected.Broadcast(this);
}

void UW_Inventory_CategoryEntry::OnButtonHovered()
{
	if (!bIsSelected)
	{
		// Visual feedback
	}
}

void UW_Inventory_CategoryEntry::OnButtonUnhovered()
{
	if (!bIsSelected)
	{
		// Revert visual feedback
	}
}
