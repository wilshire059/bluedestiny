#include "W_UserWidget_Base.h"

void UW_UserWidget_Base::NativeConstruct()
{
    Super::NativeConstruct();
    RefreshComponents();
}

void UW_UserWidget_Base::RefreshComponents()
{
    if (AActor* Owner = GetOwningPlayerPawn())
    {
        EquipmentManager = Owner->FindComponentByClass<UAC_EquipmentManager>();
        CombatManager = Owner->FindComponentByClass<UAC_CombatManager>();
        InventoryManager = Owner->FindComponentByClass<UAC_InventoryManager>();
        StatManager = Owner->FindComponentByClass<UAC_StatManager>();
        ProgressManager = Owner->FindComponentByClass<UAC_ProgressManager>();
    }
}

UAC_EquipmentManager* UW_UserWidget_Base::GetEquipmentComponent()
{
    if (!EquipmentManager) RefreshComponents();
    return EquipmentManager;
}

UAC_CombatManager* UW_UserWidget_Base::GetCombatComponent()
{
    if (!CombatManager) RefreshComponents();
    return CombatManager;
}

UAC_InventoryManager* UW_UserWidget_Base::GetInventoryComponent()
{
    if (!InventoryManager) RefreshComponents();
    return InventoryManager;
}

UAC_StatManager* UW_UserWidget_Base::GetStatComponent()
{
    if (!StatManager) RefreshComponents();
    return StatManager;
}

UAC_ProgressManager* UW_UserWidget_Base::GetProgressComponent()
{
    if (!ProgressManager) RefreshComponents();
    return ProgressManager;
}
