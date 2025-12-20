#include "AC_AI_CombatManager.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/AC_InventoryManager.h"
#include "Classes/B_Stat.h"
#include "Interfaces/BPI_Enemy.h"
#include "Interfaces/BPI_Controller.h"

UAC_AI_CombatManager::UAC_AI_CombatManager()
{
    PrimaryComponentTick.bCanEverTick = false;
    CurrencyReward = 100;
    bHealthbarActive = false;
    bUseWorldHealthbar = false;
    HealthBarDuration = 5.0f;
    DelayAfterDeath = 2.0f;
}

void UAC_AI_CombatManager::BeginPlay()
{
    Super::BeginPlay();

    // Bind to parent death delegate
    OnDeath.AddDynamic(this, &UAC_AI_CombatManager::OnDeathHandler);
}

void UAC_AI_CombatManager::HandleAIDeath(bool bRagdoll, E_Direction Direction, AActor* Killer)
{
    bIsDead = true;

    // Display death VFX
    DisplayDeathVfx();

    // Spawn loot
    PickAndSpawnLoot();

    // Award currency to killer
    if (Killer)
    {
        APawn* KillerPawn = Cast<APawn>(Killer);
        if (KillerPawn && KillerPawn->GetController())
        {
            if (KillerPawn->GetController()->Implements<UBPI_Controller>())
            {
                UAC_InventoryManager* Inventory = IBPI_Controller::Execute_GetInventoryComponent(KillerPawn->GetController());
                if (Inventory)
                {
                    Inventory->AdjustCurrency(CurrencyReward);
                }
            }
        }
    }

    // Broadcast AI death
    OnAIDeath.Broadcast(bRagdoll, Direction, Killer);

    // Disable healthbar after delay
    if (UWorld* World = GetWorld())
    {
        World->GetTimerManager().SetTimer(HealthbarTimer, this, &UAC_AI_CombatManager::DisableHealthbar, DelayAfterDeath, false);
    }
}

void UAC_AI_CombatManager::OnDeathHandler(bool bRagdoll, E_Direction Direction, AActor* Killer)
{
    HandleAIDeath(bRagdoll, Direction, Killer);
}

void UAC_AI_CombatManager::EndEncounter()
{
    // Spawn loot
    PickAndSpawnLoot();

    // Additional cleanup logic can be added here
}

UObject* UAC_AI_CombatManager::TryGetAbility()
{
    // Base implementation returns nullptr
    // Subclasses or Blueprints should override to select abilities from ability pool
    return nullptr;
}

bool UAC_AI_CombatManager::ExecuteAbility(UObject* Ability)
{
    // Base implementation validates ability and returns success
    // Subclasses should override with actual ability execution logic
    if (!Ability)
    {
        return false;
    }
    return true;
}

void UAC_AI_CombatManager::PickAndSpawnLoot()
{
    AActor* Owner = GetOwner();
    if (Owner && Owner->Implements<UBPI_Enemy>())
    {
        IBPI_Enemy::Execute_PickAndSpawnLoot(Owner);
    }
}

void UAC_AI_CombatManager::DisplayDeathVfx()
{
    AActor* Owner = GetOwner();
    if (Owner && Owner->Implements<UBPI_Enemy>())
    {
        IBPI_Enemy::Execute_DisplayDeathVfx(Owner, Owner->GetActorLocation());
    }
}

void UAC_AI_CombatManager::DisableHealthbar()
{
    ToggleHealthbarVisual(false);
    EndEncounter();
}

void UAC_AI_CombatManager::ToggleHealthbarVisual(bool bVisible)
{
    bHealthbarActive = bVisible;

    AActor* Owner = GetOwner();
    if (Owner && Owner->Implements<UBPI_Enemy>())
    {
        IBPI_Enemy::Execute_ToggleHealthbarVisual(Owner, bVisible);
    }
}

void UAC_AI_CombatManager::UpdateEnemyHealth(float HealthPercent)
{
    // Show healthbar if not visible
    if (!bHealthbarActive)
    {
        ToggleHealthbarVisual(true);
    }

    OnEnemyHealthUpdated.Broadcast(HealthPercent);

    // Reset healthbar timer
    if (UWorld* World = GetWorld())
    {
        World->GetTimerManager().ClearTimer(HealthbarLosTimer);
        World->GetTimerManager().SetTimer(HealthbarLosTimer, this, &UAC_AI_CombatManager::DisableHealthbar, HealthBarDuration, false);
    }
}

UAC_InventoryManager* UAC_AI_CombatManager::GetInventoryComponent() const
{
    AActor* Owner = GetOwner();
    if (Owner)
    {
        return Owner->FindComponentByClass<UAC_InventoryManager>();
    }
    return nullptr;
}

TArray<FStatInfo> UAC_AI_CombatManager::GetAllStats() const
{
    TArray<FStatInfo> AllStats;

    for (const auto& StatPair : ActiveStats)
    {
        if (UB_Stat* Stat = StatPair.Value)
        {
            FStatInfo Info;
            Info.Tag = StatPair.Key;
            Info.Value = Stat->CurrentValue;
            Info.MaxValue = Stat->MaxValue;
            AllStats.Add(Info);
        }
    }

    return AllStats;
}

UAnimInstance* UAC_AI_CombatManager::GetSoulslikeAnimInstance() const
{
    AActor* Owner = GetOwner();
    if (ACharacter* Character = Cast<ACharacter>(Owner))
    {
        if (USkeletalMeshComponent* MeshComp = Character->GetMesh())
        {
            return MeshComp->GetAnimInstance();
        }
    }
    return nullptr;
}
