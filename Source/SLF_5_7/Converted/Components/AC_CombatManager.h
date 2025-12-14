#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Enums/E_Direction.h"
#include "AC_CombatManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnDeath, bool, bRagdoll, E_Direction, KillingBlowDirection, AActor*, Killer);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPoiseBroken);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDamageTaken, float, Damage);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SLF_5_7_API UAC_CombatManager : public UActorComponent
{
    GENERATED_BODY()

public:    
    UAC_CombatManager();

    UPROPERTY(BlueprintAssignable, Category = "Combat")
    FOnDeath OnDeath;

    UPROPERTY(BlueprintAssignable, Category = "Combat")
    FOnPoiseBroken OnPoiseBroken;

    UPROPERTY(BlueprintAssignable, Category = "Combat")
    FOnDamageTaken OnDamageTaken;

    UFUNCTION(BlueprintCallable, Category = "Combat")
    void HandleDeath(bool bRagdoll, E_Direction Direction, AActor* Killer);

    UFUNCTION(BlueprintCallable, Category = "Combat")
    void HandlePoiseBreak();

    UFUNCTION(BlueprintCallable, Category = "Combat")
    void ProcessDamage(float DamageAmount, AActor* Instigator);

    // Combo System Stubs
    UFUNCTION(BlueprintCallable, Category = "Combat")
    void AttemptAttack();

    UFUNCTION(BlueprintCallable, Category = "Combat")
    void ResetCombo();

protected:
    virtual void BeginPlay() override;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
    bool bIsDead;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
    int32 CurrentComboIndex;
};
