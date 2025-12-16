#pragma once

#include "CoreMinimal.h"
#include "Components/AC_CombatManager.h"
#include "GameplayTagContainer.h"
#include "Enums/E_Direction.h"
#include "AC_AI_CombatManager.generated.h"

class UB_Stat;
class UAC_InventoryManager;
class UAnimMontage;
class UPDA_Item;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnAIDeathDelegate, bool, bRagdoll, E_Direction, Direction, AActor*, Killer);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnemyHealthUpdated, float, HealthPercent);

UCLASS(ClassGroup = (Custom), Blueprintable, meta = (BlueprintSpawnableComponent))
class SLF_5_7_API UAC_AI_CombatManager : public UAC_CombatManager
{
    GENERATED_BODY()

public:
    UAC_AI_CombatManager();

    // ============================================================
    // PROPERTIES - AI SPECIFIC
    // ============================================================

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Combat|State")
    int32 CurrencyReward;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Combat|State")
    bool bHealthbarActive;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Combat|State")
    bool bUseWorldHealthbar;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Combat|State")
    float HealthBarDuration;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Combat|State")
    FTimerHandle HealthbarTimer;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Combat|State")
    FTimerHandle HealthbarLosTimer;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Combat|Death")
    float DelayAfterDeath;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Combat|Death")
    TObjectPtr<UAnimMontage> DeathMontage;

    // ============================================================
    // DELEGATES
    // ============================================================

    UPROPERTY(BlueprintAssignable, Category = "AI Combat")
    FOnAIDeathDelegate OnAIDeath;

    UPROPERTY(BlueprintAssignable, Category = "AI Combat")
    FOnEnemyHealthUpdated OnEnemyHealthUpdated;

    // ============================================================
    // AI SPECIFIC FUNCTIONS
    // ============================================================

    UFUNCTION(BlueprintCallable, Category = "AI Combat")
    void EndEncounter();

    UFUNCTION(BlueprintCallable, Category = "AI Combat")
    UObject* TryGetAbility();

    UFUNCTION(BlueprintCallable, Category = "AI Combat")
    bool ExecuteAbility(UObject* Ability);

    UFUNCTION(BlueprintCallable, Category = "AI Combat|Death")
    void PickAndSpawnLoot();

    UFUNCTION(BlueprintCallable, Category = "AI Combat|Death")
    void DisplayDeathVfx();

    UFUNCTION(BlueprintCallable, Category = "AI Combat|Healthbar")
    void ToggleHealthbarVisual(bool bVisible);

    UFUNCTION(BlueprintCallable, Category = "AI Combat|Healthbar")
    void UpdateEnemyHealth(float HealthPercent);

    UFUNCTION(BlueprintPure, Category = "AI Combat|Equipment")
    UAC_InventoryManager* GetInventoryComponent() const;

    UFUNCTION(BlueprintCallable, Category = "AI Combat|Death")
    void HandleAIDeath(bool bRagdoll, E_Direction Direction, AActor* Killer);

protected:
    virtual void BeginPlay() override;

    UFUNCTION()
    void OnDeathHandler(bool bRagdoll, E_Direction Direction, AActor* Killer);

    UFUNCTION()
    void DisableHealthbar();
};
