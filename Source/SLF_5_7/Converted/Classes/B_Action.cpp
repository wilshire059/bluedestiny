#include "B_Action.h"
#include "Components/AC_EquipmentManager.h"
#include "Components/AC_StatManager.h"
#include "DataAssets/PDA_WeaponAnimset.h"
#include "DataAssets/PDA_Action.h"
#include "Interfaces/BPI_Generic_Character.h"
#include "GameFramework/Character.h"

UB_Action::UB_Action()
{

}

void UB_Action::ExecuteAction_Implementation()
{
    // Default implementation or logic from graph
}

UPDA_WeaponAnimset* UB_Action::GetWeaponAnimset(E_ActionWeaponSlot WeaponSlot)
{
    // Logic from Blueprint: Get Equipment Manager -> Check active slot -> return Animset
    if (UAC_EquipmentManager* EquipmentManager = GetEquipmentManager())
    {
        // Need conversion from E_ActionWeaponSlot to GameplayTag logic or direct access
        // For now stubbing to return nullptr or first available
        return nullptr; 
    }
    return nullptr;
}

bool UB_Action::CheckStatRequirement(E_ActionWeaponSlot StaminaMultiplierWeaponSlot)
{
    if (UAC_StatManager* StatManager = GetStatManager())
    {
        // Check stats
        return true; 
    }
    return true; 
}

UAnimInstance* UB_Action::GetOwnerAnimInstance()
{
    if (OwnerActor)
    {
        if (OwnerActor->Implements<UBPI_Generic_Character>())
        {
            return IBPI_Generic_Character::Execute_GetSoulslikeAnimInstance(OwnerActor);
        }
        else if (ACharacter* Char = Cast<ACharacter>(OwnerActor))
        {
            return Char->GetMesh()->GetAnimInstance();
        }
    }
    return nullptr;
}

UAC_EquipmentManager* UB_Action::GetEquipmentManager() const
{
    if (OwnerActor)
    {
        return OwnerActor->FindComponentByClass<UAC_EquipmentManager>();
    }
    return nullptr;
}

UAC_StatManager* UB_Action::GetStatManager() const
{
    if (OwnerActor)
    {
        return OwnerActor->FindComponentByClass<UAC_StatManager>();
    }
    return nullptr;
}
