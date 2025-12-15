#pragma once

#include "CoreMinimal.h"
#include "Components/AC_CombatManager.h"
#include "AC_AI_CombatManager.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SLF_5_7_API UAC_AI_CombatManager : public UAC_CombatManager
{
    GENERATED_BODY()

public:    
    UAC_AI_CombatManager();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Combat")
    int32 CurrencyReward;

    UFUNCTION(BlueprintCallable, Category = "AI Combat")
    void EndEncounter();

    UFUNCTION(BlueprintCallable, Category = "AI Combat")
    UObject* TryGetAbility();

    UFUNCTION(BlueprintCallable, Category = "AI Combat")
    bool ExecuteAbility(UObject* Ability);
    
protected:
    virtual void BeginPlay() override;

    UFUNCTION()
    void OnDeathHandler(bool bRagdoll, E_Direction Direction, AActor* Killer);

    UFUNCTION()
    void DisableHealthbar();
};
