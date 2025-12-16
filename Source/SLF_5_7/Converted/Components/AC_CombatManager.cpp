#include "AC_CombatManager.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Controller.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/AC_StatManager.h"
#include "Components/AC_EquipmentManager.h"
#include "Components/AC_SaveLoadManager.h"
#include "Classes/B_Stat.h"

UAC_CombatManager::UAC_CombatManager()
{
    PrimaryComponentTick.bCanEverTick = true;
    bIsDead = false;
    CurrentComboIndex = 0;
    bRagdollOnDeath = false;
    bIsGuarding = false;
    GuardActivationTime = 0.0f;
    Currency = 0;
    CurrentState = E_AI_States::Idle;
    DefaultComboSequenceSection = NAME_None;
}

void UAC_CombatManager::BeginPlay()
{
    Super::BeginPlay();
}

// ============================================================
// DEATH & DAMAGE
// ============================================================

void UAC_CombatManager::HandleDeath(UAC_StatManager* StatManager, const FHitResult& HitInfo)
{
    if (bIsDead)
    {
        return;
    }

    // Check if health stat is <= 0
    if (StatManager)
    {
        if (UB_Stat* HealthStat = StatManager->GetStat(FGameplayTag::RequestGameplayTag(FName("Stat.Health"))))
        {
            if (HealthStat->CurrentValue > 0.0f)
            {
                return;
            }
        }
    }

    bIsDead = true;

    // Get direction from hit
    E_Direction KillingBlowDir = GetDirectionFromHit(HitInfo);

    // Broadcast death event
    OnDeath.Broadcast(bRagdollOnDeath, KillingBlowDir, nullptr);
}

void UAC_CombatManager::EnableRagdoll()
{
    // Would call BPI_GenericCharacter::EnableRagdoll on the owner
    // Placeholder: implementation depends on the character class
}

void UAC_CombatManager::StartRespawn(float FadeDelay)
{
    // Would call BPI_GenericCharacter::StartRespawn on the controller
    // Placeholder: implementation depends on the controller class
}

void UAC_CombatManager::DropCurrency()
{
    // Implementation depends on currency pickup actor spawning
}

FVector UAC_CombatManager::GetBossDoorCurrencyDropLocation() const
{
    AActor* Owner = GetOwner();
    return Owner ? Owner->GetActorLocation() : FVector::ZeroVector;
}

FVector UAC_CombatManager::GetDeathCurrencySpawnPoint() const
{
    AActor* Owner = GetOwner();
    return Owner ? Owner->GetActorLocation() : FVector::ZeroVector;
}

// ============================================================
// DAMAGE PROCESSING
// ============================================================

void UAC_CombatManager::HandleIncomingWeaponDamage(AActor* DamagingActor, const FHitResult& HitResult, float BaseDamage, const FGameplayTagContainer& DamageTags)
{
    if (bIsDead)
    {
        return;
    }

    // Calculate final damage
    float FinalDamage = CalculateWeaponDamage(BaseDamage, 0.0f);

    // Get direction for reaction
    E_Direction HitDirection = GetDirectionFromHit(HitResult);

    // Check if guarding
    if (bIsGuarding && GetIsFacingEnemy())
    {
        // Reduce damage while guarding
        FinalDamage *= 0.2f;
        // Play guard hit reaction
    }
    else
    {
        // Apply hit reaction
        HandleHitReaction(HitDirection, FinalDamage > 50.0f);
    }

    // Apply status effects
    ApplyIncomingStatusEffects(DamageTags);

    // Broadcast damage taken
    OnDamageTaken.Broadcast(FinalDamage);
}

void UAC_CombatManager::HandleIncomingWeaponDamage_AI(AActor* DamagingActor, const FHitResult& HitResult, float BaseDamage, const FGameplayTagContainer& DamageTags)
{
    // AI-specific damage handling
    HandleIncomingWeaponDamage(DamagingActor, HitResult, BaseDamage, DamageTags);

    // Set AI state to combat
    SetState(E_AI_States::Combat, FInstancedStruct());
    SetTarget(DamagingActor);
}

float UAC_CombatManager::CalculateWeaponDamage(float BaseDamage, float AdditionalModifier) const
{
    return BaseDamage + AdditionalModifier;
}

void UAC_CombatManager::HandleHitReaction(E_Direction Direction, bool bIsMajorHit)
{
    // Look up reaction montage from animset
    if (const TSoftObjectPtr<UAnimMontage>* ReactionMontage = ReactionAnimset.Find(Direction))
    {
        if (!ReactionMontage->IsNull())
        {
            PlaySoftMontageReplicated(*ReactionMontage, 1.0f, 0.0f, NAME_None, bIsMajorHit);
        }
    }
}

void UAC_CombatManager::HandlePoiseBreak()
{
    OnPoiseBroken.Broadcast();
}

void UAC_CombatManager::ProcessDamage(float DamageAmount, AActor* Instigator)
{
    if (bIsDead)
    {
        return;
    }

    OnDamageTaken.Broadcast(DamageAmount);
}

E_Direction UAC_CombatManager::GetDirectionFromHit(const FHitResult& HitResult) const
{
    AActor* Owner = GetOwner();
    if (!Owner)
    {
        return E_Direction::Forward;
    }

    FVector HitDirection = HitResult.ImpactNormal;
    FVector OwnerForward = Owner->GetActorForwardVector();

    float Dot = FVector::DotProduct(HitDirection, OwnerForward);

    if (Dot > 0.5f)
    {
        return E_Direction::Backward;
    }
    else if (Dot < -0.5f)
    {
        return E_Direction::Forward;
    }
    else
    {
        FVector Cross = FVector::CrossProduct(OwnerForward, HitDirection);
        return Cross.Z > 0.0f ? E_Direction::Left : E_Direction::Right;
    }
}

float UAC_CombatManager::GetKnockbackAmountForDamage(float Damage) const
{
    return Damage * 10.0f;
}

float UAC_CombatManager::GetStaminaDrainAmountForDamage(float Damage) const
{
    return Damage * 0.5f;
}

void UAC_CombatManager::ApplyIncomingStatusEffects(const FGameplayTagContainer& EffectTags)
{
    // Iterate through effect tags and apply status effects
}

void UAC_CombatManager::AddOneShotBuildup(FGameplayTag EffectTag, float Amount)
{
    // Add one-shot buildup for status effects like poison, bleed, etc.
}

// ============================================================
// GUARDING
// ============================================================

void UAC_CombatManager::SetGuardState(bool bToggled, bool bIgnoreGracePeriod)
{
    bIsGuarding = bToggled;
    if (bToggled)
    {
        GuardActivationTime = GetWorld() ? GetWorld()->GetTimeSeconds() : 0.0f;
    }
}

bool UAC_CombatManager::GetIsGuarding() const
{
    return bIsGuarding;
}

float UAC_CombatManager::GetTimeSinceGuardActivation() const
{
    if (!bIsGuarding || !GetWorld())
    {
        return 0.0f;
    }
    return GetWorld()->GetTimeSeconds() - GuardActivationTime;
}

TSoftObjectPtr<UAnimMontage> UAC_CombatManager::GetGuardHitMontage() const
{
    // Would look up from equipment or animset
    return TSoftObjectPtr<UAnimMontage>();
}

// ============================================================
// COMBAT ACTIONS
// ============================================================

void UAC_CombatManager::AttemptAttack()
{
    // Logic to play attack montage based on weapon and combo index
    CurrentComboIndex++;
}

void UAC_CombatManager::ResetCombo()
{
    CurrentComboIndex = 0;
}

void UAC_CombatManager::ProcessHandTrace(bool bLeftHand)
{
    // Perform trace from hand socket for unarmed combat
}

void UAC_CombatManager::ApplyFistDamage(AActor* TargetActor, const FHitResult& HitResult)
{
    if (!TargetActor)
    {
        return;
    }

    float BaseDamage = 10.0f; // Unarmed base damage
    UGameplayStatics::ApplyPointDamage(
        TargetActor,
        BaseDamage,
        HitResult.ImpactNormal,
        HitResult,
        GetOwner()->GetInstigatorController(),
        GetOwner(),
        nullptr
    );
}

void UAC_CombatManager::PlayIkReaction(E_Direction Direction)
{
    // Play procedural IK-based hit reaction
}

void UAC_CombatManager::StartHitstop(float Duration)
{
    if (UWorld* World = GetWorld())
    {
        // Slow down time briefly
        UGameplayStatics::SetGlobalTimeDilation(World, 0.01f);
        FTimerHandle TimerHandle;
        World->GetTimerManager().SetTimer(TimerHandle, [World]()
        {
            UGameplayStatics::SetGlobalTimeDilation(World, 1.0f);
        }, Duration, false);
    }
}

void UAC_CombatManager::StartCameraShake(TSubclassOf<UCameraShakeBase> ShakeClass, float Scale)
{
    if (AActor* Owner = GetOwner())
    {
        if (APawn* Pawn = Cast<APawn>(Owner))
        {
            if (APlayerController* PC = Cast<APlayerController>(Pawn->GetController()))
            {
                PC->ClientStartCameraShake(ShakeClass, Scale);
            }
        }
    }
}

// ============================================================
// LOCK-ON SYSTEM
// ============================================================

void UAC_CombatManager::ResetLockOn()
{
    CurrentTarget = nullptr;
    OnTargetLocked.Broadcast(nullptr, false);
}

void UAC_CombatManager::ToggleLockonWidget(bool bVisible)
{
    // Toggle visibility of lock-on indicator widget
}

void UAC_CombatManager::OnTargetLocked_Internal(AActor* Target, bool bLocked)
{
    CurrentTarget = bLocked ? Target : nullptr;
    OnTargetLocked.Broadcast(Target, bLocked);
}

bool UAC_CombatManager::GetIsFacingEnemy() const
{
    if (!CurrentTarget)
    {
        return false;
    }

    AActor* Owner = GetOwner();
    if (!Owner)
    {
        return false;
    }

    FVector ToEnemy = (CurrentTarget->GetActorLocation() - Owner->GetActorLocation()).GetSafeNormal();
    float Dot = FVector::DotProduct(Owner->GetActorForwardVector(), ToEnemy);

    return Dot > 0.5f;
}

// ============================================================
// STATS & CURRENCY
// ============================================================

UB_Stat* UAC_CombatManager::GetStat(FGameplayTag StatTag, FStatInfo& OutStatInfo) const
{
    if (const TObjectPtr<UB_Stat>* FoundStat = ActiveStats.Find(StatTag))
    {
        OutStatInfo = (*FoundStat)->GetStatInfo();
        return *FoundStat;
    }
    return nullptr;
}

float UAC_CombatManager::GetStatCurrentValue(const FStatInfo& StatInfo) const
{
    return StatInfo.Value;
}

float UAC_CombatManager::GetStatMaxValue(FGameplayTag StatTag) const
{
    if (const TObjectPtr<UB_Stat>* FoundStat = ActiveStats.Find(StatTag))
    {
        return (*FoundStat)->MaxValue;
    }
    return 0.0f;
}

void UAC_CombatManager::AdjustStat(FGameplayTag StatTag, float Delta)
{
    if (TObjectPtr<UB_Stat>* FoundStat = ActiveStats.Find(StatTag))
    {
        (*FoundStat)->ModifyStat(Delta);
    }
}

void UAC_CombatManager::AdjustValue(UB_Stat* Stat, float Change)
{
    if (Stat)
    {
        Stat->ModifyStat(Change);
    }
}

void UAC_CombatManager::ResetStat(FGameplayTag StatTag)
{
    if (TObjectPtr<UB_Stat>* FoundStat = ActiveStats.Find(StatTag))
    {
        (*FoundStat)->SetCurrentValue((*FoundStat)->MaxValue);
    }
}

int32 UAC_CombatManager::GetCurrentCurrency() const
{
    return Currency;
}

void UAC_CombatManager::AdjustCurrency(int32 Delta)
{
    Currency = FMath::Max(0, Currency + Delta);
}

// ============================================================
// COMPONENT ACCESS
// ============================================================

UAC_EquipmentManager* UAC_CombatManager::GetEquipmentComponent(AController* Target) const
{
    if (!Target)
    {
        return nullptr;
    }

    if (APawn* ControlledPawn = Target->GetPawn())
    {
        return ControlledPawn->FindComponentByClass<UAC_EquipmentManager>();
    }
    return nullptr;
}

UAC_SaveLoadManager* UAC_CombatManager::GetSaveLoadComponent(AController* Target) const
{
    if (!Target)
    {
        return nullptr;
    }

    return Target->FindComponentByClass<UAC_SaveLoadManager>();
}

// ============================================================
// EQUIPMENT HELPERS
// ============================================================

bool UAC_CombatManager::AreBothWeaponSlotsActive() const
{
    // Check equipment component for dual wielding
    return false;
}

UPDA_Item* UAC_CombatManager::GetItemAtSlot(E_ActionWeaponSlot Slot) const
{
    // Look up item in equipment
    return nullptr;
}

E_ActionWeaponSlot UAC_CombatManager::GetActiveWeaponSlot() const
{
    return E_ActionWeaponSlot::RightHand;
}

// ============================================================
// REPLICATION & EFFECTS
// ============================================================

void UAC_CombatManager::PlayMontageReplicated(UAnimMontage* Montage, float PlayRate, float StartPosition, FName StartSection)
{
    // Would call BPI_GenericCharacter::PlayMontageReplicated on the owner
    // Placeholder: implementation depends on the character class
}

void UAC_CombatManager::PlaySoftMontageReplicated(TSoftObjectPtr<UAnimMontage> Montage, float PlayRate, float StartPosition, FName StartSection, bool bPriority)
{
    // Would call BPI_GenericCharacter::PlaySoftMontageReplicated on the owner
    // Placeholder: implementation depends on the character class
}

void UAC_CombatManager::PlaySoftSoundAtLocation(TSoftObjectPtr<USoundBase> Sound, FVector Location)
{
    if (!Sound.IsNull())
    {
        if (USoundBase* LoadedSound = Sound.LoadSynchronous())
        {
            UGameplayStatics::PlaySoundAtLocation(this, LoadedSound, Location);
        }
    }
}

void UAC_CombatManager::PlaySoftNiagaraOneshotAtLocationReplicated(TSoftObjectPtr<UNiagaraSystem> NiagaraSystem, FVector Location, FRotator Rotation)
{
    if (!NiagaraSystem.IsNull())
    {
        if (UNiagaraSystem* LoadedSystem = NiagaraSystem.LoadSynchronous())
        {
            UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, LoadedSystem, Location, Rotation);
        }
    }
}

// ============================================================
// MOVEMENT & AI
// ============================================================

void UAC_CombatManager::SetMovementMode(E_MovementType Type)
{
    // Would call BPI_GenericCharacter::SetMovementMode on the owner
    // Placeholder: implementation depends on the character class
}

void UAC_CombatManager::SetState(E_AI_States NewState, const FInstancedStruct& Data)
{
    CurrentState = NewState;

    if (UBlackboardComponent* BB = GetBlackboard())
    {
        BB->SetValueAsEnum(FName("State"), static_cast<uint8>(CurrentState));
    }
}

void UAC_CombatManager::SetKeyValue(FName KeyName, const FInstancedStruct& Data)
{
    if (UBlackboardComponent* BB = GetBlackboard())
    {
        // Similar implementation to AC_AI_BehaviorManager
    }
}

void UAC_CombatManager::SetPatrolPath(AB_PatrolPath* NewPatrolPath)
{
    PatrolPath = NewPatrolPath;
}

void UAC_CombatManager::SetTarget(AActor* NewTarget)
{
    CurrentTarget = NewTarget;

    if (UBlackboardComponent* BB = GetBlackboard())
    {
        BB->SetValueAsObject(FName("Target"), NewTarget);
    }
}

UBlackboardComponent* UAC_CombatManager::GetBlackboard() const
{
    if (AAIController* AIC = UAIBlueprintHelperLibrary::GetAIController(GetOwner()))
    {
        return AIC->GetBlackboardComponent();
    }
    return nullptr;
}

E_AI_States UAC_CombatManager::GetState() const
{
    return CurrentState;
}

// ============================================================
// SAVE SYSTEM
// ============================================================

void UAC_CombatManager::AddSpawnedInteractableToSaveData(AActor* SpawnedActor)
{
    // Add spawned interactable to save data for persistence
}
