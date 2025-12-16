#include "AC_AI_Boss.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "Components/AC_StatManager.h"
#include "Components/AC_CombatManager.h"
#include "Components/AC_AI_CombatManager.h"
#include "Components/AudioComponent.h"
#include "Classes/B_Stat.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/StreamableManager.h"
#include "Engine/AssetManager.h"
#include "Sound/SoundBase.h"
#include "Animation/AnimMontage.h"
#include "LevelSequence.h"
#include "Interfaces/BPI_Controller.h"
#include "Enums/E_AI_States.h"
#include "InstancedStruct.h"

UAC_AI_Boss::UAC_AI_Boss()
{
    PrimaryComponentTick.bCanEverTick = false;
    DeathTextDelay = 3.0f;
    ActivePhase = 0;
    bFightActive = false;
    bDebugActive = false;
}

void UAC_AI_Boss::BeginPlay()
{
    Super::BeginPlay();

    // Delay binding to ensure other components are initialized
    if (UWorld* World = GetWorld())
    {
        World->GetTimerManager().SetTimerForNextTick(this, &UAC_AI_Boss::BindToStats);
        World->GetTimerManager().SetTimerForNextTick(this, &UAC_AI_Boss::BindToDeath);
    }
}

void UAC_AI_Boss::BindToStats()
{
    if (UAC_StatManager* StatManager = GetStatManager())
    {
        // Iterate the Stats map and bind to each stat's update delegate
        for (auto& StatPair : StatManager->Stats)
        {
            if (UB_Stat* Stat = StatPair.Value)
            {
                Stat->OnStatUpdated.AddDynamic(this, &UAC_AI_Boss::OnStatUpdated);
            }
        }
    }
}

void UAC_AI_Boss::BindToDeath()
{
    if (UAC_CombatManager* CombatManager = GetCombatManager())
    {
        CombatManager->OnDeath.AddDynamic(this, &UAC_AI_Boss::OnDeathHandler);
    }
}

void UAC_AI_Boss::InitializeBoss(FText Name, float MaxHealth)
{
    BossName = Name;
    SetFightActive(true);
}

// ============================================================
// PHASE MANAGEMENT
// ============================================================

void UAC_AI_Boss::SetPhase(int32 PhaseIndex)
{
    if (!Phases.IsValidIndex(PhaseIndex))
    {
        return;
    }

    ActivePhase = PhaseIndex;
    HandlePhaseChange(Phases[PhaseIndex], PhaseIndex);
}

int32 UAC_AI_Boss::GetActivePhase() const
{
    return ActivePhase;
}

bool UAC_AI_Boss::EvaluatePhaseRequirement(const FAiRuleStat& StatRequirement) const
{
    if (UAC_StatManager* StatManager = GetStatManager())
    {
        if (UB_Stat* Stat = StatManager->GetStat(StatRequirement.StatTag))
        {
            return Stat->CurrentValue <= StatRequirement.TargetValue;
        }
    }
    return false;
}

void UAC_AI_Boss::HandlePhaseChange(const FAiBossPhase& NewPhase, int32 PhaseIndex)
{
    // Override abilities on AI Combat Manager
    if (UAC_AI_CombatManager* AICombat = GetAICombatManager())
    {
        // Would call OverrideAbilities if implemented
        // AICombat->OverrideAbilities(NewPhase.PhaseAbilities);
    }

    // Set combat manager state (reset to idle during phase transition)
    if (UAC_CombatManager* CombatManager = GetCombatManager())
    {
        FInstancedStruct EmptyData;
        CombatManager->SetState(E_AI_States::Idle, EmptyData);
    }

    // Try play phase sequence
    TryPlayPhaseSequence(NewPhase.PhaseStartSequence);

    // Try play phase montage
    TryPlayPhaseMontage(NewPhase.PhaseStartMontage);

    // Try play phase music
    TryPlayPhaseMusic(NewPhase.PhaseMusic);

    // Broadcast phase changed
    OnBossPhaseChanged.Broadcast(PhaseIndex);
}

void UAC_AI_Boss::OnStatUpdated(UB_Stat* Stat, double Change, bool bUpdateAffectedStats, E_ValueType ValueType)
{
    if (!Stat || !bFightActive)
    {
        return;
    }

    CheckPhaseTransition(Stat);
}

void UAC_AI_Boss::CheckPhaseTransition(UB_Stat* UpdatedStat)
{
    if (Phases.Num() == 0)
    {
        return;
    }

    for (int32 i = 0; i < Phases.Num(); i++)
    {
        const FAiBossPhase& Phase = Phases[i];

        // Check if this stat matches the phase requirement
        if (UpdatedStat->StatTag == Phase.RequiredStat.StatTag)
        {
            // Evaluate if we should transition
            if (EvaluatePhaseRequirement(Phase.RequiredStat))
            {
                if (i != ActivePhase)
                {
                    SetPhase(i);
                    break;
                }
            }
        }
    }
}

// ============================================================
// FIGHT STATE
// ============================================================

void UAC_AI_Boss::SetFightActive(bool bActive)
{
    bFightActive = bActive;

    if (bActive)
    {
        TryLockBossDoors();
        OnBossFightStarted.Broadcast();
    }
    else
    {
        OnBossFightEnded.Broadcast();
    }
}

bool UAC_AI_Boss::IsFightActive() const
{
    return bFightActive;
}

// ============================================================
// DEATH HANDLING
// ============================================================

void UAC_AI_Boss::OnDeathHandler(bool bRagdoll, E_Direction Direction, AActor* Killer)
{
    SetFightActive(false);
    Instigator = Killer;

    // Show death text after delay
    if (DeathTextDelay > 0.0f)
    {
        if (UWorld* World = GetWorld())
        {
            World->GetTimerManager().SetTimer(
                DeathTextTimerHandle,
                this,
                &UAC_AI_Boss::ShowDeathText,
                DeathTextDelay,
                false
            );
        }
    }
    else
    {
        ShowDeathText();
    }

    // Play death sequence
    TryPlayDeathSequence();

    // Unlock boss doors
    TryGetBossDoors();
    TryUnlockBossDoors();

    // Stop music
    StopPhaseMusic(2.0f);

    OnBossDefeated.Broadcast();
}

void UAC_AI_Boss::ShowDeathText()
{
    // Get the target (instigator's controller)
    if (Instigator)
    {
        if (APawn* InstigatorPawn = Cast<APawn>(Instigator))
        {
            if (AController* Controller = InstigatorPawn->GetController())
            {
                if (Controller->Implements<UBPI_Controller>())
                {
                    IBPI_Controller::Execute_SendBigScreenMessage(
                        Controller,
                        DeathText,
                        nullptr, // Gradient material
                        true,    // Backdrop
                        1.0f     // Play rate
                    );
                }
            }
        }
    }
}

// ============================================================
// BOSS DOORS
// ============================================================

void UAC_AI_Boss::TryGetBossDoors()
{
    // Placeholder - would query the level for boss door actors
}

void UAC_AI_Boss::TryUnlockBossDoors()
{
    // Placeholder - would unlock all boss doors
}

void UAC_AI_Boss::TryLockBossDoors()
{
    // Placeholder - would lock all boss doors
}

// ============================================================
// SEQUENCES & MONTAGES
// ============================================================

void UAC_AI_Boss::TryPlayPhaseSequence(TSoftObjectPtr<ULevelSequence> PhaseSequence)
{
    if (!PhaseSequence.IsValid() && !PhaseSequence.IsNull())
    {
        // Async load
        FStreamableManager& Streamable = UAssetManager::GetStreamableManager();
        Streamable.RequestAsyncLoad(
            PhaseSequence.ToSoftObjectPath(),
            FStreamableDelegate::CreateWeakLambda(this, [this, PhaseSequence]()
            {
                OnPhaseSequenceLoaded(PhaseSequence);
            })
        );
    }
    else if (PhaseSequence.IsValid())
    {
        OnPhaseSequenceLoaded(PhaseSequence);
    }
}

void UAC_AI_Boss::OnPhaseSequenceLoaded(TSoftObjectPtr<ULevelSequence> LoadedSequence)
{
    if (ULevelSequence* Sequence = LoadedSequence.Get())
    {
        // Would play the level sequence
        // This requires level sequence player setup
    }
}

void UAC_AI_Boss::TryPlayPhaseMontage(TSoftObjectPtr<UAnimMontage> PhaseMontage)
{
    if (!PhaseMontage.IsValid() && !PhaseMontage.IsNull())
    {
        // Async load
        FStreamableManager& Streamable = UAssetManager::GetStreamableManager();
        Streamable.RequestAsyncLoad(
            PhaseMontage.ToSoftObjectPath(),
            FStreamableDelegate::CreateWeakLambda(this, [this, PhaseMontage]()
            {
                OnPhaseMontageLoaded(PhaseMontage);
            })
        );
    }
    else if (PhaseMontage.IsValid())
    {
        OnPhaseMontageLoaded(PhaseMontage);
    }
}

void UAC_AI_Boss::OnPhaseMontageLoaded(TSoftObjectPtr<UAnimMontage> LoadedMontage)
{
    if (UAnimMontage* Montage = LoadedMontage.Get())
    {
        if (AActor* Owner = GetOwner())
        {
            if (ACharacter* Character = Cast<ACharacter>(Owner))
            {
                if (UAnimInstance* AnimInstance = Character->GetMesh()->GetAnimInstance())
                {
                    AnimInstance->Montage_Play(Montage);
                }
            }
        }
    }
}

void UAC_AI_Boss::TryPlayDeathSequence()
{
    TryPlayPhaseSequence(DeathSequence);
}

// ============================================================
// AUDIO
// ============================================================

void UAC_AI_Boss::TryPlayPhaseMusic(TSoftObjectPtr<USoundBase> PhaseMusic)
{
    if (PhaseMusic.IsNull())
    {
        return;
    }

    if (!PhaseMusic.IsValid())
    {
        // Async load
        FStreamableManager& Streamable = UAssetManager::GetStreamableManager();
        Streamable.RequestAsyncLoad(
            PhaseMusic.ToSoftObjectPath(),
            FStreamableDelegate::CreateWeakLambda(this, [this, PhaseMusic]()
            {
                OnPhaseMusicLoaded(PhaseMusic);
            })
        );
    }
    else
    {
        OnPhaseMusicLoaded(PhaseMusic);
    }
}

void UAC_AI_Boss::OnPhaseMusicLoaded(TSoftObjectPtr<USoundBase> LoadedMusic)
{
    if (USoundBase* Sound = LoadedMusic.Get())
    {
        // Fade out current music if playing
        if (ActiveMusicComponent && ActiveMusicComponent->IsPlaying())
        {
            ActiveMusicComponent->FadeOut(1.0f, 0.0f);
        }

        // Spawn new music component
        ActiveMusicComponent = UGameplayStatics::SpawnSound2D(
            this,
            Sound,
            1.0f, // Volume
            1.0f, // Pitch
            0.0f, // Start time
            nullptr, // Concurrency
            false, // Persist across level transition
            false  // Auto destroy
        );

        if (ActiveMusicComponent)
        {
            ActiveMusicComponent->FadeIn(1.0f, 1.0f, 0.0f);
        }
    }
}

void UAC_AI_Boss::StopPhaseMusic(float FadeOutDuration)
{
    if (ActiveMusicComponent && ActiveMusicComponent->IsPlaying())
    {
        ActiveMusicComponent->FadeOut(FadeOutDuration, 0.0f);
    }
}

// ============================================================
// COMPONENT ACCESSORS
// ============================================================

UAC_StatManager* UAC_AI_Boss::GetStatManager() const
{
    AActor* Owner = GetOwner();
    if (Owner)
    {
        return Owner->FindComponentByClass<UAC_StatManager>();
    }
    return nullptr;
}

UAC_CombatManager* UAC_AI_Boss::GetCombatManager() const
{
    AActor* Owner = GetOwner();
    if (Owner)
    {
        return Owner->FindComponentByClass<UAC_CombatManager>();
    }
    return nullptr;
}

UAC_AI_CombatManager* UAC_AI_Boss::GetAICombatManager() const
{
    AActor* Owner = GetOwner();
    if (Owner)
    {
        return Owner->FindComponentByClass<UAC_AI_CombatManager>();
    }
    return nullptr;
}
