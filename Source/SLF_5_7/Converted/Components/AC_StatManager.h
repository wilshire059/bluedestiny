#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "Enums/E_ValueType.h"
#include "DataAssets/PDA_Calculations.h"
#include "Structs/FStatInfo.h"
#include "Classes/B_Stat.h"
#include "Structs/FSaveGameInfo.h"
#include "AC_StatManager.generated.h"

class UAC_SaveLoadManager;
class UPDA_BaseCharacterInfo;

// Delegate declarations
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLevelUpdated, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLevelUpRequested, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStatsInitialized);

UCLASS(ClassGroup=(Custom), Blueprintable, meta=(BlueprintSpawnableComponent))
class SLF_5_7_API UAC_StatManager : public UActorComponent
{
    GENERATED_BODY()

public:
    UAC_StatManager();

    // ============================================================
    // DELEGATES
    // ============================================================

    UPROPERTY(BlueprintAssignable, Category = "Stats")
    FOnLevelUpdated OnLevelUpdated;

    UPROPERTY(BlueprintAssignable, Category = "Stats")
    FOnLevelUpRequested OnLevelUpRequested;

    UPROPERTY(BlueprintAssignable, Category = "Stats")
    FOnStatsInitialized OnStatsInitialized;

    // ============================================================
    // PROPERTIES
    // ============================================================

    // Stats container (used by existing code)
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats")
    TMap<FGameplayTag, TObjectPtr<UB_Stat>> Stats;

    // Current character level (used by existing code)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    int32 CurrentLevel;

    // Whether this is an AI-controlled component (affects level updates)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    bool bIsAiComponent;

    // Type of calculation for stat modifiers
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    E_CalculationType CalculationType;

    // Stat classes to instantiate on initialization
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Configuration")
    TArray<TSubclassOf<UB_Stat>> StatClasses;

    // ============================================================
    // INITIALIZATION FUNCTIONS
    // ============================================================

    // Called from BeginPlay, sets up stats and binds to save system
    UFUNCTION(BlueprintCallable, Category = "Stats|Initialization")
    void EventInitializeStats();

    // Called when save data is loaded
    UFUNCTION(BlueprintCallable, Category = "Stats|Initialization")
    void EventOnDataLoaded(FSaveGameInfo SaveGameInfo);

    // ============================================================
    // CORE STAT FUNCTIONS
    // ============================================================

    // Get a stat by its tag
    UFUNCTION(BlueprintCallable, Category = "Stats")
    UB_Stat* GetStat(FGameplayTag StatTag);

    // Get stat and its info
    UFUNCTION(BlueprintCallable, Category = "Stats")
    UB_Stat* GetStatWithInfo(FGameplayTag StatTag, FStatInfo& OutStatInfo);

    // Modify a stat value
    UFUNCTION(BlueprintCallable, Category = "Stats")
    void ModifyStat(FGameplayTag StatTag, float Value, E_ValueType ValueType);

    // ============================================================
    // LEVEL FUNCTIONS
    // ============================================================

    // Adjust the character level by delta
    UFUNCTION(BlueprintCallable, Category = "Stats|Level")
    void AdjustLevel(int32 Delta);

    // ============================================================
    // AFFECTED STATS FUNCTIONS
    // ============================================================

    // Process affected stats when a stat changes
    UFUNCTION(BlueprintCallable, Category = "Stats|Affected")
    void AdjustAffectedStats(UB_Stat* Stat, double Change, E_ValueType ValueType);

    // Adjust a specific affected stat by tag
    UFUNCTION(BlueprintCallable, Category = "Stats|Affected")
    void AdjustAffected(FGameplayTag StatTag, E_ValueType ValueType, double Change);

    // Adjust affected stat value
    UFUNCTION(BlueprintCallable, Category = "Stats|Affected")
    void AdjustAffectedValue(FGameplayTag StatTag, E_ValueType ValueType, double Change);

    // Calculate modifier based on calculation type
    UFUNCTION(BlueprintCallable, Category = "Stats|Calculation")
    double Calculate(double Modifier, double ChangeAmount);

    // ============================================================
    // SAVE/LOAD FUNCTIONS
    // ============================================================

    // Initialize stats from loaded save data
    UFUNCTION(BlueprintCallable, Category = "Stats|SaveLoad")
    void InitializeLoadedStats(const TArray<FStatInfo>& LoadedStats);

    // Update a stat's info from save data
    UFUNCTION(BlueprintCallable, Category = "Stats|SaveLoad")
    void UpdateStatInfo(UB_Stat* Stat, const FStatInfo& NewStatInfo);

    // Get save load component from player controller
    UFUNCTION(BlueprintPure, Category = "Stats|SaveLoad")
    UAC_SaveLoadManager* GetSaveLoadComponent() const;

    // Get selected character class from game instance
    UFUNCTION(BlueprintPure, Category = "Stats|SaveLoad")
    UPDA_BaseCharacterInfo* GetSelectedClass() const;

    // ============================================================
    // EVENT HANDLERS
    // ============================================================

    // Called when a stat is updated
    UFUNCTION()
    void OnStatUpdatedHandler(UB_Stat* UpdatedStat, double Change, bool bUpdateAffectedStats, E_ValueType ValueType);

    // Called when level up is requested
    UFUNCTION()
    void OnLevelUpRequestedHandler(int32 Delta);

protected:
    virtual void BeginPlay() override;

private:
    // Helper to check if array is valid (has elements)
    template<typename T>
    bool IsValidArray(const TArray<T>& InArray) const { return InArray.Num() > 0; }
};
