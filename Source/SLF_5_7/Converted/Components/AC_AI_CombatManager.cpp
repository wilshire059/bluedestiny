#include "AC_AI_CombatManager.h"
#include "Interfaces/BPI_Enemy.h"
#include "Interfaces/BPI_Controller.h"
#include "Components/AC_InventoryManager.h"
#include "GameFramework/Controller.h"
#include "Kismet/KismetSystemLibrary.h"

UAC_AI_CombatManager::UAC_AI_CombatManager()
{
    CurrencyReward = 100;
}

void UAC_AI_CombatManager::BeginPlay()
{
    Super::BeginPlay();
    
    // Bind to parent delegate
    OnDeath.AddDynamic(this, &UAC_AI_CombatManager::OnDeathHandler);
}

void UAC_AI_CombatManager::OnDeathHandler(bool bRagdoll, E_Direction Direction, AActor* Killer)
{
    // Give Currency to Killer
    if (Killer)
    {
        APawn* KillerPawn = Cast<APawn>(Killer);
        if (KillerPawn)
        {
            if (KillerPawn->GetController() && KillerPawn->GetController()->Implements<UBPI_Controller>())
            {
                UAC_InventoryManager* Inventory = IBPI_Controller::Execute_GetInventoryComponent(KillerPawn->GetController());
                if (Inventory)
                {
                    Inventory->AdjustCurrency(CurrencyReward);
                }
            }
        }
    }

    // Visuals
    if (GetOwner()->Implements<UBPI_Enemy>())
    {
        IBPI_Enemy::Execute_DisplayDeathVfx(GetOwner(), GetOwner()->GetActorLocation());
    }

    // Timer to disable UI
    FTimerHandle Handle;
    GetWorld()->GetTimerManager().SetTimer(Handle, this, &UAC_AI_CombatManager::DisableHealthbar, 2.0f, false);
}

void UAC_AI_CombatManager::DisableHealthbar()
{
    if (GetOwner()->Implements<UBPI_Enemy>())
    {
        IBPI_Enemy::Execute_ToggleHealthbarVisual(GetOwner(), false);
    }
    EndEncounter();
}

void UAC_AI_CombatManager::EndEncounter()
{
    // Logic to notify GameState or Managers
    // Spawn Loot
     if (GetOwner()->Implements<UBPI_Enemy>())
    {
        IBPI_Enemy::Execute_PickAndSpawnLoot(GetOwner());
    }
    
    // Destroy Actor logic deferred to BP or specialized cleanup
}
