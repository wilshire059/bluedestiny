// W_Inventory_CategoryEntry.cpp

#include "W_Inventory_CategoryEntry.h"
#include "Components/Button.h"
#include "Styling/SlateColor.h"

UW_Inventory_CategoryEntry::UW_Inventory_CategoryEntry(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, bAllCategoriesButton(false)
	, bSelected(false)
	, HoverTintColor(FLinearColor(0.85f, 0.74f, 0.62f, 1.0f))
	, UnhoverTintColor(FLinearColor(0.49f, 0.39f, 0.28f, 1.0f))
{
}

void UW_Inventory_CategoryEntry::NativePreConstruct()
{
	Super::NativePreConstruct();

	// Set initial icon if category data is valid
	if (CategoryIcon && !InventoryCategoryData.CategoryIcon.IsNull())
	{
		CategoryIcon->SetBrushFromSoftTexture(InventoryCategoryData.CategoryIcon);
	}
}

void UW_Inventory_CategoryEntry::NativeConstruct()
{
	Super::NativeConstruct();

	if (Button)
	{
		Button->OnClicked.AddDynamic(this, &UW_Inventory_CategoryEntry::OnButtonClicked);
		Button->OnHovered.AddDynamic(this, &UW_Inventory_CategoryEntry::OnButtonHovered);
		Button->OnUnhovered.AddDynamic(this, &UW_Inventory_CategoryEntry::OnButtonUnhovered);
	}

	// Set initial visual state
	if (CategoryIcon)
	{
		CategoryIcon->SetBrushTintColor(bSelected ? HoverTintColor : UnhoverTintColor);
	}

	// Hide selected glow by default
	if (SelectedGlow)
	{
		SelectedGlow->SetVisibility(bSelected ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
	}
}

void UW_Inventory_CategoryEntry::SetInventoryCategorySelected(bool bNewSelected, const FSlateColor& NewHoveredColor, const FSlateColor& NewUnhoveredColor)
{
	bSelected = bNewSelected;
	HoverTintColor = NewHoveredColor;
	UnhoverTintColor = NewUnhoveredColor;

	if (CategoryIcon)
	{
		CategoryIcon->SetBrushTintColor(bSelected ? HoverTintColor : UnhoverTintColor);
	}

	if (SelectedGlow)
	{
		SelectedGlow->SetVisibility(bSelected ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
	}
}

void UW_Inventory_CategoryEntry::OnButtonClicked()
{
	bSelected = true;

	if (CategoryIcon)
	{
		CategoryIcon->SetBrushTintColor(HoverTintColor);
	}

	if (SelectedGlow)
	{
		SelectedGlow->SetVisibility(ESlateVisibility::Visible);
	}

	// Broadcast selected event with category info
	OnSelected.Broadcast(this, InventoryCategoryData.CategoryEnum);
}

void UW_Inventory_CategoryEntry::OnButtonHovered()
{
	if (!bSelected && CategoryIcon)
	{
		CategoryIcon->SetBrushTintColor(HoverTintColor);
	}
}

void UW_Inventory_CategoryEntry::OnButtonUnhovered()
{
	if (!bSelected && CategoryIcon)
	{
		CategoryIcon->SetBrushTintColor(UnhoverTintColor);
	}
}
