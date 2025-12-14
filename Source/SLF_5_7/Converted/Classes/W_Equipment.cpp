#include "W_Equipment.h"

void UW_Equipment::NavigateSlots(bool bNext)
{
    if (!CanNavigate()) return;

    if (bNext)
    {
        EquipmentSlotNavigationIndex = FMath::Clamp(EquipmentSlotNavigationIndex + 1, 0, EquipmentSlots.Num() - 1);
    }
    else
    {
        EquipmentSlotNavigationIndex = FMath::Clamp(EquipmentSlotNavigationIndex - 1, 0, EquipmentSlots.Num() - 1);
    }
}
