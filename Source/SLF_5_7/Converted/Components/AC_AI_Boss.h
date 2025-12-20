#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "Structs/FAiBossPhase.h"
#include "Enums/E_ValueType.h"
#include "Enums/E_Direction.h"
#include "AC_AI_Boss.generated.h"

class UAC_StatManager;
class UAC_CombatManager;
class UAC_AI_CombatManager;
class UB_Stat;
class UAudioComponent;
class ULevelSequencePlayer;
class UAnimMontage;
class USoundBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBossPhaseChanged, int32, NewPhaseIndex);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBossFightStarted);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBossFightEnded);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBossDefeated);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBossEncounterStarted);

UCLASS(ClassGroup = (Custom), Blueprintable, meta = (BlueprintSpawnableComponent))
class SLF_5_7_API UAC_AI_Boss : public UActorComponent
{
    GENERATED_BODY()

public:
    UAC_AI_Boss();

    // ============================================================
    // PROPERTIES - BOSS INFO
    // ============================================================

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Boss|Info")
    FText BossName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Boss|Info")
    FText DeathText;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Boss|Info")
    float DeathTextDelay;

    // ============================================================
    // PROPERTIES - PHASES
    // ============================================================

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Boss|Phases")
    TArray<FAiBossPhase> Phases;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Boss|Phases")
    int32 ActivePhase;

    // ============================================================
    // PROPERTIES - SEQUENCES
    // ============================================================

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Boss|Sequences")
    TSoftObjectPtr<ULevelSequence> DeathSequence;

    // ============================================================
    // PROPERTIES - AUDIO
    // ============================================================

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Boss|Audio")
    TObjectPtr<UAudioComponent> ActiveMusicComponent;

    // ============================================================
    // PROPERTIES - STATE
    // ============================================================

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Boss|State")
    bool bFightActive;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Boss|State")
    bool bDebugActive;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Boss|State")
    TObjectPtr<AActor> Instigator;

    // ============================================================
    // PROPERTIES - TIMERS
    // ============================================================

    UPROPERTY()
    FTimerHandle DeathTextTimerHandle;

    // ============================================================
    // DELEGATES
    // ============================================================

    UPROPERTY(BlueprintAssignable, Category = "AI Boss")
    FOnBossPhaseChanged OnBossPhaseChanged;

    UPROPERTY(BlueprintAssignable, Category = "AI Boss")
    FOnBossFightStarted OnBossFightStarted;

    UPROPERTY(BlueprintAssignable, Category = "AI Boss")
    FOnBossFightEnded OnBossFightEnded;

    UPROPERTY(BlueprintAssignable, Category = "AI Boss")
    FOnBossDefeated OnBossDefeated;

    UPROPERTY(BlueprintAssignable, Category = "AI Boss")
    FOnBossEncounterStarted OnBossEncounterStarted;

    // ============================================================
    // INITIALIZATION
    // ============================================================

    UFUNCTION(BlueprintCallable, Category = "AI Boss")
    void InitializeBoss(FText Name, float MaxHealth);

    // ============================================================
    // PHASE MANAGEMENT
    // ============================================================

    UFUNCTION(BlueprintCallable, Category = "AI Boss|Phase")
    void SetPhase(int32 PhaseIndex);

    UFUNCTION(BlueprintPure, Category = "AI Boss|Phase")
    int32 GetActivePhase() const;

    UFUNCTION(BlueprintPure, Category = "AI Boss|Phase")
    bool EvaluatePhaseRequirement(const FAiRuleStat& StatRequirement) const;

    UFUNCTION(BlueprintCallable, Category = "AI Boss|Phase")
    void HandlePhaseChange(const FAiBossPhase& NewPhase, int32 PhaseIndex);

    // ============================================================
    // FIGHT STATE
    // ============================================================

    UFUNCTION(BlueprintCallable, Category = "AI Boss|Fight")
    void SetFightActive(bool bActive);

    UFUNCTION(BlueprintPure, Category = "AI Boss|Fight")
    bool IsFightActive() const;

    // ============================================================
    // BOSS DOORS
    // ============================================================

    UFUNCTION(BlueprintCallable, Category = "AI Boss|Doors")
    void TryGetBossDoors();

    UFUNCTION(BlueprintCallable, Category = "AI Boss|Doors")
    void TryUnlockBossDoors();

    UFUNCTION(BlueprintCallable, Category = "AI Boss|Doors")
    void TryLockBossDoors();

    // ============================================================
    // SEQUENCES & MONTAGES
    // ============================================================

    UFUNCTION(BlueprintCallable, Category = "AI Boss|Sequence")
    void TryPlayPhaseSequence(TSoftObjectPtr<ULevelSequence> PhaseSequence);

    UFUNCTION(BlueprintCallable, Category = "AI Boss|Montage")
    void TryPlayPhaseMontage(TSoftObjectPtr<UAnimMontage> PhaseMontage);

    UFUNCTION(BlueprintCallable, Category = "AI Boss|Sequence")
    void TryPlayDeathSequence();

    // ============================================================
    // AUDIO
    // ============================================================

    UFUNCTION(BlueprintCallable, Category = "AI Boss|Audio")
    void TryPlayPhaseMusic(TSoftObjectPtr<USoundBase> PhaseMusic);

    UFUNCTION(BlueprintCallable, Category = "AI Boss|Audio")
    void StopPhaseMusic(float FadeOutDuration = 1.0f);

    // ============================================================
    // DEATH HANDLING
    // ============================================================

    UFUNCTION(BlueprintCallable, Category = "AI Boss|Death")
    void ShowDeathText();

    // ============================================================
    // COMPONENT ACCESSORS
    // ============================================================

    UFUNCTION(BlueprintPure, Category = "AI Boss|Components")
    UAC_StatManager* GetStatManager() const;

    UFUNCTION(BlueprintPure, Category = "AI Boss|Components")
    UAC_CombatManager* GetCombatManager() const;

    UFUNCTION(BlueprintPure, Category = "AI Boss|Components")
    UAC_AI_CombatManager* GetAICombatManager() const;

protected:
    virtual void BeginPlay() override;

    UFUNCTION()
    void OnStatUpdated(UB_Stat* Stat, double Change, bool bUpdateAffectedStats, E_ValueType ValueType);

    UFUNCTION()
    void OnDeathHandler(bool bRagdoll, E_Direction Direction, AActor* Killer);

    void BindToStats();
    void BindToDeath();
    void CheckPhaseTransition(UB_Stat* UpdatedStat);

private:
    void OnPhaseMusicLoaded(TSoftObjectPtr<USoundBase> LoadedMusic);
    void OnPhaseSequenceLoaded(TSoftObjectPtr<ULevelSequence> LoadedSequence);
    void OnPhaseMontageLoaded(TSoftObjectPtr<UAnimMontage> LoadedMontage);
};
