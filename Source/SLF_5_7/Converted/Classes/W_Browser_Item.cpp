#include "W_Browser_Item.h"

void UW_Browser_Item::NativeConstruct()
{
	Super::NativeConstruct();

	if (ItemButton)
	{
		ItemButton->OnClicked.AddDynamic(this, &UW_Browser_Item::HandleItemClicked);
	}
}

void UW_Browser_Item::SetupItem(int32 InItemIndex, FText ItemName, UTexture2D* Icon)
{
	ItemIndex = InItemIndex;

	if (ItemNameText)
	{
		ItemNameText->SetText(ItemName);
	}

	if (ItemIcon && Icon)
	{
		ItemIcon->SetBrushFromTexture(Icon);
	}
}

void UW_Browser_Item::HandleItemClicked()
{
	OnBrowserItemSelected.Broadcast(ItemIndex);
}

void UW_Browser_Item::SetSelected(bool bSelected)
{
	// Visual feedback for selection - implemented in Blueprint
}
