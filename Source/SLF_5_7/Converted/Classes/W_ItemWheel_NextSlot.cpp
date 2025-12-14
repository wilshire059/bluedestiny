#include "W_ItemWheel_NextSlot.h"

void UW_ItemWheel_NextSlot::UpdateSlotDisplay(UTexture2D* Icon)
{
	if (ItemIcon && Icon)
	{
		ItemIcon->SetBrushFromTexture(Icon);
		ItemIcon->SetVisibility(ESlateVisibility::Visible);
	}
}

void UW_ItemWheel_NextSlot::ClearSlot()
{
	if (ItemIcon)
	{
		ItemIcon->SetVisibility(ESlateVisibility::Collapsed);
	}
}
