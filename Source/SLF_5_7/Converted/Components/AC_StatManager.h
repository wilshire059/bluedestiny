#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "Enums/E_ValueType.h"
#include "Classes/B_Stat.h"
#include "AC_StatManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLevelUpRequested, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStatsInitialized);

UCLASS( ClassGroup=(Custom), Blueprintable, meta=(BlueprintSpawnableComponent) )
class SLF_5_7_API UAC_StatManager : public UActorComponent
{
    GENERATED_BODY()

public:    
    UAC_StatManager();

    // Stats Container
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats")
    TMap<FGameplayTag, UB_Stat*> Stats;
    
    // Core Functions
    UFUNCTION(BlueprintCallable, Category = "Stats")
    void InitializeStats();

    UFUNCTION(BlueprintCallable, Category = "Stats")
    UB_Stat* GetStat(FGameplayTag StatTag);

    UFUNCTION(BlueprintCallable, Category = "Stats")
    void ModifyStat(FGameplayTag StatTag, float Value, E_ValueType ValueType);

    UFUNCTION(BlueprintCallable, Category = "Stats")
    void AdjustAffectedStats(UB_Stat* Stat, float Change, E_ValueType ValueType);

    // Leveling
    UFUNCTION(BlueprintCallable, Category = "Stats")
    void AdjustLevel(int32 Delta);

    UPROPERTY(BlueprintAssignable, Category = "Stats")
    FOnLevelUpRequested OnLevelUpRequested;

    UPROPERTY(BlueprintAssignable, Category = "Stats")
    FOnStatsInitialized OnStatsInitialized;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    int32 CurrentLevel;

protected:
    virtual void BeginPlay() override;
};
