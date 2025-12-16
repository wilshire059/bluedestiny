#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "Enums/E_Direction.h"
#include "Enums/E_MovementType.h"
#include "Enums/E_ActionWeaponSlot.h"
#include "Enums/E_AI_States.h"
#include "Structs/FStatInfo.h"
#include "StructUtils/InstancedStruct.h"
#include "AC_CombatManager.generated.h"

class UAC_StatManager;
class UAC_EquipmentManager;
class UAC_SaveLoadManager;
class UB_Stat;
class UBlackboardComponent;
class AB_PatrolPath;
class UAnimMontage;
class UNiagaraSystem;
class USoundBase;
class UPDA_Item;
class UCameraShakeBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnDeath, bool, bRagdoll, E_Direction, KillingBlowDirection, AActor*, Killer);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPoiseBroken);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDamageTaken, float, Damage);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnTargetLocked, AActor*, Target, bool, bLocked);

UCLASS(ClassGroup = (Custom), Blueprintable, meta = (BlueprintSpawnableComponent))
class SLF_5_7_API UAC_CombatManager : public UActorComponent
{
    GENERATED_BODY()

public:
    UAC_CombatManager();

    // ============================================================
    // PROPERTIES
    // ============================================================

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
    bool bIsDead;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
    int32 CurrentComboIndex;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
    bool bRagdollOnDeath;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
    bool bIsGuarding;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
    float GuardActivationTime;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
    TObjectPtr<AActor> CurrentTarget;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
    FVector CurrentHitNormal;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
    E_AI_States CurrentState;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
    TMap<FGameplayTag, TObjectPtr<UB_Stat>> ActiveStats;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
    int32 Currency;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
    FName DefaultComboSequenceSection;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
    TMap<E_Direction, TSoftObjectPtr<UAnimMontage>> ReactionAnimset;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    TObjectPtr<AB_PatrolPath> PatrolPath;

    // ============================================================
    // DELEGATES
    // ============================================================

    UPROPERTY(BlueprintAssignable, Category = "Combat")
    FOnDeath OnDeath;

    UPROPERTY(BlueprintAssignable, Category = "Combat")
    FOnPoiseBroken OnPoiseBroken;

    UPROPERTY(BlueprintAssignable, Category = "Combat")
    FOnDamageTaken OnDamageTaken;

    UPROPERTY(BlueprintAssignable, Category = "Combat")
    FOnTargetLocked OnTargetLocked;

    // ============================================================
    // DEATH & DAMAGE
    // ============================================================

    UFUNCTION(BlueprintCallable, Category = "Combat|Death")
    void HandleDeath(UAC_StatManager* StatManager, const FHitResult& HitInfo);

    UFUNCTION(BlueprintCallable, Category = "Combat|Death")
    void EnableRagdoll();

    UFUNCTION(BlueprintCallable, Category = "Combat|Death")
    void StartRespawn(float FadeDelay);

    UFUNCTION(BlueprintCallable, Category = "Combat|Death")
    void DropCurrency();

    UFUNCTION(BlueprintPure, Category = "Combat|Death")
    FVector GetBossDoorCurrencyDropLocation() const;

    UFUNCTION(BlueprintPure, Category = "Combat|Death")
    FVector GetDeathCurrencySpawnPoint() const;

    // ============================================================
    // DAMAGE PROCESSING
    // ============================================================

    UFUNCTION(BlueprintCallable, Category = "Combat|Damage")
    void HandleIncomingWeaponDamage(AActor* DamagingActor, const FHitResult& HitResult, float BaseDamage, const FGameplayTagContainer& DamageTags);

    UFUNCTION(BlueprintCallable, Category = "Combat|Damage")
    void HandleIncomingWeaponDamage_AI(AActor* DamagingActor, const FHitResult& HitResult, float BaseDamage, const FGameplayTagContainer& DamageTags);

    UFUNCTION(BlueprintCallable, Category = "Combat|Damage")
    float CalculateWeaponDamage(float BaseDamage, float AdditionalModifier) const;

    UFUNCTION(BlueprintCallable, Category = "Combat|Damage")
    void HandleHitReaction(E_Direction Direction, bool bIsMajorHit);

    UFUNCTION(BlueprintCallable, Category = "Combat|Damage")
    void HandlePoiseBreak();

    UFUNCTION(BlueprintCallable, Category = "Combat|Damage")
    void ProcessDamage(float DamageAmount, AActor* Instigator);

    UFUNCTION(BlueprintPure, Category = "Combat|Damage")
    E_Direction GetDirectionFromHit(const FHitResult& HitResult) const;

    UFUNCTION(BlueprintPure, Category = "Combat|Damage")
    float GetKnockbackAmountForDamage(float Damage) const;

    UFUNCTION(BlueprintPure, Category = "Combat|Damage")
    float GetStaminaDrainAmountForDamage(float Damage) const;

    UFUNCTION(BlueprintCallable, Category = "Combat|Damage")
    void ApplyIncomingStatusEffects(const FGameplayTagContainer& EffectTags);

    UFUNCTION(BlueprintCallable, Category = "Combat|Damage")
    void AddOneShotBuildup(FGameplayTag EffectTag, float Amount);

    // ============================================================
    // GUARDING
    // ============================================================

    UFUNCTION(BlueprintCallable, Category = "Combat|Guard")
    void SetGuardState(bool bToggled, bool bIgnoreGracePeriod);

    UFUNCTION(BlueprintPure, Category = "Combat|Guard")
    bool GetIsGuarding() const;

    UFUNCTION(BlueprintPure, Category = "Combat|Guard")
    float GetTimeSinceGuardActivation() const;

    UFUNCTION(BlueprintPure, Category = "Combat|Guard")
    TSoftObjectPtr<UAnimMontage> GetGuardHitMontage() const;

    // ============================================================
    // COMBAT ACTIONS
    // ============================================================

    UFUNCTION(BlueprintCallable, Category = "Combat|Actions")
    void AttemptAttack();

    UFUNCTION(BlueprintCallable, Category = "Combat|Actions")
    void ResetCombo();

    UFUNCTION(BlueprintCallable, Category = "Combat|Actions")
    void ProcessHandTrace(bool bLeftHand);

    UFUNCTION(BlueprintCallable, Category = "Combat|Actions")
    void ApplyFistDamage(AActor* TargetActor, const FHitResult& HitResult);

    UFUNCTION(BlueprintCallable, Category = "Combat|Actions")
    void PlayIkReaction(E_Direction Direction);

    UFUNCTION(BlueprintCallable, Category = "Combat|Actions")
    void StartHitstop(float Duration);

    UFUNCTION(BlueprintCallable, Category = "Combat|Actions")
    void StartCameraShake(TSubclassOf<UCameraShakeBase> ShakeClass, float Scale);

    // ============================================================
    // LOCK-ON SYSTEM
    // ============================================================

    UFUNCTION(BlueprintCallable, Category = "Combat|LockOn")
    void ResetLockOn();

    UFUNCTION(BlueprintCallable, Category = "Combat|LockOn")
    void ToggleLockonWidget(bool bVisible);

    UFUNCTION(BlueprintCallable, Category = "Combat|LockOn")
    void OnTargetLocked_Internal(AActor* Target, bool bLocked);

    UFUNCTION(BlueprintPure, Category = "Combat|LockOn")
    bool GetIsFacingEnemy() const;

    // ============================================================
    // STATS & CURRENCY
    // ============================================================

    UFUNCTION(BlueprintPure, Category = "Combat|Stats")
    UB_Stat* GetStat(FGameplayTag StatTag, FStatInfo& OutStatInfo) const;

    UFUNCTION(BlueprintPure, Category = "Combat|Stats")
    float GetStatCurrentValue(const FStatInfo& StatInfo) const;

    UFUNCTION(BlueprintPure, Category = "Combat|Stats")
    float GetStatMaxValue(FGameplayTag StatTag) const;

    UFUNCTION(BlueprintCallable, Category = "Combat|Stats")
    void AdjustStat(FGameplayTag StatTag, float Delta);

    UFUNCTION(BlueprintCallable, Category = "Combat|Stats")
    void AdjustValue(UB_Stat* Stat, float Change);

    UFUNCTION(BlueprintCallable, Category = "Combat|Stats")
    void ResetStat(FGameplayTag StatTag);

    UFUNCTION(BlueprintPure, Category = "Combat|Currency")
    int32 GetCurrentCurrency() const;

    UFUNCTION(BlueprintCallable, Category = "Combat|Currency")
    void AdjustCurrency(int32 Delta);

    // ============================================================
    // COMPONENT ACCESS
    // ============================================================

    UFUNCTION(BlueprintPure, Category = "Combat|Components")
    UAC_EquipmentManager* GetEquipmentComponent(AController* Target) const;

    UFUNCTION(BlueprintPure, Category = "Combat|Components")
    UAC_SaveLoadManager* GetSaveLoadComponent(AController* Target) const;

    // ============================================================
    // EQUIPMENT HELPERS
    // ============================================================

    UFUNCTION(BlueprintPure, Category = "Combat|Equipment")
    bool AreBothWeaponSlotsActive() const;

    UFUNCTION(BlueprintPure, Category = "Combat|Equipment")
    UPDA_Item* GetItemAtSlot(E_ActionWeaponSlot Slot) const;

    UFUNCTION(BlueprintPure, Category = "Combat|Equipment")
    E_ActionWeaponSlot GetActiveWeaponSlot() const;

    // ============================================================
    // REPLICATION & EFFECTS
    // ============================================================

    UFUNCTION(BlueprintCallable, Category = "Combat|Replication")
    void PlayMontageReplicated(UAnimMontage* Montage, float PlayRate, float StartPosition, FName StartSection);

    UFUNCTION(BlueprintCallable, Category = "Combat|Replication")
    void PlaySoftMontageReplicated(TSoftObjectPtr<UAnimMontage> Montage, float PlayRate, float StartPosition, FName StartSection, bool bPriority);

    UFUNCTION(BlueprintCallable, Category = "Combat|Effects")
    void PlaySoftSoundAtLocation(TSoftObjectPtr<USoundBase> Sound, FVector Location);

    UFUNCTION(BlueprintCallable, Category = "Combat|Effects")
    void PlaySoftNiagaraOneshotAtLocationReplicated(TSoftObjectPtr<UNiagaraSystem> NiagaraSystem, FVector Location, FRotator Rotation);

    // ============================================================
    // MOVEMENT & AI
    // ============================================================

    UFUNCTION(BlueprintCallable, Category = "Combat|Movement")
    void SetMovementMode(E_MovementType Type);

    UFUNCTION(BlueprintCallable, Category = "Combat|AI")
    void SetState(E_AI_States NewState, const FInstancedStruct& Data);

    UFUNCTION(BlueprintCallable, Category = "Combat|AI")
    void SetKeyValue(FName KeyName, const FInstancedStruct& Data);

    UFUNCTION(BlueprintCallable, Category = "Combat|AI")
    void SetPatrolPath(AB_PatrolPath* NewPatrolPath);

    UFUNCTION(BlueprintCallable, Category = "Combat|AI")
    void SetTarget(AActor* NewTarget);

    UFUNCTION(BlueprintPure, Category = "Combat|AI")
    UBlackboardComponent* GetBlackboard() const;

    UFUNCTION(BlueprintPure, Category = "Combat|AI")
    E_AI_States GetState() const;

    // ============================================================
    // SAVE SYSTEM
    // ============================================================

    UFUNCTION(BlueprintCallable, Category = "Combat|Save")
    void AddSpawnedInteractableToSaveData(AActor* SpawnedActor);

protected:
    virtual void BeginPlay() override;
};
