#include "B_SoulslikeAnimInstance.h"

void UB_SoulslikeAnimInstance::NativeInitializeAnimation()
{
    Super::NativeInitializeAnimation();

    if (AActor* Owner = GetOwningActor())
    {
        EquipmentManager = Owner->FindComponentByClass<UAC_EquipmentManager>();
        CombatManager = Owner->FindComponentByClass<UAC_CombatManager>();
    }
}

void UB_SoulslikeAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);
    
    // Potentially refresh components if null, though Init is usually enough
    if (!EquipmentManager || !CombatManager)
    {
         if (AActor* Owner = GetOwningActor())
        {
            if (!EquipmentManager) EquipmentManager = Owner->FindComponentByClass<UAC_EquipmentManager>();
            if (!CombatManager) CombatManager = Owner->FindComponentByClass<UAC_CombatManager>();
        }
    }
}

UAC_EquipmentManager* UB_SoulslikeAnimInstance::GetEquipmentComponent()
{
    return EquipmentManager;
}

UAC_CombatManager* UB_SoulslikeAnimInstance::GetCombatComponent()
{
    return CombatManager;
}
