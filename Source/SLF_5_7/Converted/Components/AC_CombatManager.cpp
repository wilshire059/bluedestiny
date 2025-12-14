#include "AC_CombatManager.h"
#include "GameFramework/Actor.h"

UAC_CombatManager::UAC_CombatManager()
{
    PrimaryComponentTick.bCanEverTick = true;
    bIsDead = false;
    CurrentComboIndex = 0;
}

void UAC_CombatManager::BeginPlay()
{
    Super::BeginPlay();
}

void UAC_CombatManager::HandleDeath(bool bRagdoll, E_Direction Direction, AActor* Killer)
{
    if (bIsDead) return;
    bIsDead = true;

    OnDeath.Broadcast(bRagdoll, Direction, Killer);
    
    // Logic for ragdoll or animation would go here or be handled by the owning Actor via the delegate
}

void UAC_CombatManager::HandlePoiseBreak()
{
    OnPoiseBroken.Broadcast();
}

void UAC_CombatManager::ProcessDamage(float DamageAmount, AActor* Instigator)
{
    if (bIsDead) return;

    OnDamageTaken.Broadcast(DamageAmount);
    
    // Check Health via StatManager if available
    // Check Poise
}

void UAC_CombatManager::AttemptAttack()
{
    // Logic to play montage based on weapon and combo index
}

void UAC_CombatManager::ResetCombo()
{
    CurrentComboIndex = 0;
}
