#include "AC_AI_Boss.h"
#include "Components/AC_AI_CombatManager.h"
#include "Classes/B_Stat.h"
#include "Kismet/GameplayStatics.h"

UAC_AI_Boss::UAC_AI_Boss()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UAC_AI_Boss::BeginPlay()
{
    Super::BeginPlay();

    // Bind to Stat Updates
    if (AActor* Owner = GetOwner())
    {
        if (UAC_StatManager* StatManager = Owner->GetComponentByClass<UAC_StatManager>())
        {
             // For each stat in manager? Or specific logic?
             // Blueprint binds to *individual* stats after getting them. 
             // We'll assume logic binds to all or specific Health stats in InitializeBoss or similar.
             // Or we iterate now if initialized.
             // Optimization: Iterate stats and bind OnStatUpdated
        }
    }
}

void UAC_AI_Boss::InitializeBoss(FText Name, float MaxHealth)
{
    BossName = Name;
    // Set Health Stat?
    
    // Bind to stats
    if (AActor* Owner = GetOwner())
    {
        if (UAC_StatManager* StatManager = Owner->GetComponentByClass<UAC_StatManager>())
        {
            TArray<UB_Stat*> Stats; // Need helper or GetNodes
            // Accessing internal map is hard unless exposed. 
            // Blueprint used "GetAllStats". 
            // We need to ensure AC_StatManager exposes iteration or keys.
            // Assuming we bind to stats matching our Phase criteria whenever they update.
            // Workaround: Bind all via manager? No, manager doesn't broadcast all.
            // We iterate keys from Manager API.
        }
    }
}

void UAC_AI_Boss::OnStatUpdated(UB_Stat* Stat, double Amount, double Percent)
{
    // Check Phases
    for (int32 i = 0; i < Phases.Num(); i++)
    {
        const FAiBossPhase& Phase = Phases[i];
        if (Stat->StatTag == Phase.RequiredStat.StatTag) 
        {
            // Check threshold
            // B_Stat usually stores CurrentValue. 
            // Logic: Is Current <= Target? (Phase transition usually on health drop)
            if (Stat->CurrentValue <= Phase.RequiredStat.TargetValue)
            {
                 HandlePhaseChange(Phase, i);
            }
        }
    }
}

void UAC_AI_Boss::HandlePhaseChange(const FAiBossPhase& NewPhase, int32 PhaseIndex)
{
    // Trigger Logic
    // Override Abilities on Combat Manager
    if (UAC_AI_CombatManager* AICombat = GetOwner()->GetComponentByClass<UAC_AI_CombatManager>())
    {
        // AICombat->OverrideAbilities(NewPhase.Abilities); // Stub or Implement
    }
    
    // Play Music
    // UGameplayStatics::PlaySound...
    
    OnBossPhaseChanged.Broadcast(PhaseIndex);
}
