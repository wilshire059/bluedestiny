#include "W_InventoryAction.h"

void UW_InventoryAction::UpdateOkInputIcons(TSoftObjectPtr<UTexture2D> OkInputTexture)
{
    if (OkInputIcon)
    {
        OkInputIcon->SetBrushFromSoftTexture(OkInputTexture);
    }
}

void UW_InventoryAction::UpdateBackInputIcons(TSoftObjectPtr<UTexture2D> BackInputTexture)
{
    if (BackInputIcon)
    {
        BackInputIcon->SetBrushFromSoftTexture(BackInputTexture);
    }
}
