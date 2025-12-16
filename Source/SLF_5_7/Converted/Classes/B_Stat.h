#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Structs/FRegen.h"
#include "Structs/FStatInfo.h"
#include "Enums/E_ValueType.h"
#include "GameplayTagContainer.h"
#include "B_Stat.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnStatChanged, double, NewValue, double, MaxValue, double, Percent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnStatUpdated, UB_Stat*, UpdatedStat, double, Change, bool, bUpdateAffectedStats, E_ValueType, ValueType);

UCLASS(Blueprintable, BlueprintType)
class SLF_5_7_API UB_Stat : public UObject
{
    GENERATED_BODY()

public:
    UB_Stat();

    // Support GetWorld for Timers
    virtual UWorld* GetWorld() const override;

    UFUNCTION(BlueprintCallable, Category = "Stat")
    void Initialize(float InBaseValue, float InMaxValue);

    UFUNCTION(BlueprintCallable, Category = "Stat")
    void ModifyStat(float Amount);

    UFUNCTION(BlueprintCallable, Category = "Stat")
    void SetCurrentValue(float NewValue);

    UFUNCTION(BlueprintCallable, Category = "Stat")
    float GetPercent() const;

    UFUNCTION(BlueprintCallable, Category = "Stat")
    void ToggleRegen(bool bEnable);

    // Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat", meta = (ExposeOnSpawn = "true"))
    FGameplayTag StatTag;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
    float BaseValue;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
    float MaxValue;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stat")
    float CurrentValue;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
    FRegen RegenConfig;

    UPROPERTY(BlueprintAssignable, Category = "Stat")
    FOnStatChanged OnStatChanged;

    UPROPERTY(BlueprintAssignable, Category = "Stat")
    FOnStatUpdated OnStatUpdated;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
    FStatInfo StatInfo;

    // Update stat from loaded info
    UFUNCTION(BlueprintCallable, Category = "Stat")
    void UpdateStatInfo(const FStatInfo& NewStatInfo);

    // Get stat info struct
    UFUNCTION(BlueprintPure, Category = "Stat")
    FStatInfo GetStatInfo() const;

protected:
    FTimerHandle RegenTimerHandle;
    
    UFUNCTION()
    void OnRegenTick();
};
