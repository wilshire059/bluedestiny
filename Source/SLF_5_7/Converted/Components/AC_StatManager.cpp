#include "AC_StatManager.h"
#include "Components/AC_SaveLoadManager.h"
#include "DataAssets/PDA_BaseCharacterInfo.h"
#include "Structs/FSaveGameInfo.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"

UAC_StatManager::UAC_StatManager()
{
    PrimaryComponentTick.bCanEverTick = false;
    CurrentLevel = 1;
    bIsAiComponent = false;
    CalculationType = E_CalculationType::Multiply;
}

void UAC_StatManager::BeginPlay()
{
    Super::BeginPlay();

    // Initialize stats on begin play
    EventInitializeStats();

    // Bind to save system if not AI
    if (!bIsAiComponent)
    {
        if (UAC_SaveLoadManager* SaveLoadComp = GetSaveLoadComponent())
        {
            SaveLoadComp->OnDataLoaded.AddDynamic(this, &UAC_StatManager::EventOnDataLoaded);
        }
    }
}

// ============================================================
// INITIALIZATION FUNCTIONS
// ============================================================

void UAC_StatManager::EventInitializeStats()
{
    // Create stat objects from configured classes
    for (const TSubclassOf<UB_Stat>& StatClass : StatClasses)
    {
        if (StatClass)
        {
            UB_Stat* NewStat = NewObject<UB_Stat>(this, StatClass);
            if (NewStat)
            {
                // Add to stats map using the stat's tag
                Stats.Add(NewStat->StatTag, NewStat);

                // Bind to stat updates
                NewStat->OnStatUpdated.AddDynamic(this, &UAC_StatManager::OnStatUpdatedHandler);
            }
        }
    }

    // Broadcast initialization complete
    OnStatsInitialized.Broadcast();
}

void UAC_StatManager::EventOnDataLoaded(FSaveGameInfo SaveGameInfo)
{
    // Called when save data is loaded
    // Apply character level from save
    CurrentLevel = SaveGameInfo.CharacterLevel;
}

// ============================================================
// CORE STAT FUNCTIONS
// ============================================================

UB_Stat* UAC_StatManager::GetStat(FGameplayTag StatTag)
{
    if (TObjectPtr<UB_Stat>* FoundStat = Stats.Find(StatTag))
    {
        return *FoundStat;
    }
    return nullptr;
}

UB_Stat* UAC_StatManager::GetStatWithInfo(FGameplayTag StatTag, FStatInfo& OutStatInfo)
{
    if (UB_Stat* Stat = GetStat(StatTag))
    {
        OutStatInfo = Stat->GetStatInfo();
        return Stat;
    }
    return nullptr;
}

void UAC_StatManager::ModifyStat(FGameplayTag StatTag, float Value, E_ValueType ValueType)
{
    UB_Stat* Stat = GetStat(StatTag);
    if (!Stat) return;

    // Handle ValueType (Flat vs Percent)
    float Change = Value;
    if (ValueType == E_ValueType::Percentage)
    {
        Change = Stat->MaxValue * (Value / 100.0f);
    }

    Stat->ModifyStat(Change);
}

// ============================================================
// LEVEL FUNCTIONS
// ============================================================

void UAC_StatManager::AdjustLevel(int32 Delta)
{
    // Only process if not AI component
    if (bIsAiComponent)
    {
        return;
    }

    // Adjust level
    CurrentLevel = CurrentLevel + Delta;

    // Broadcast level change to both delegates
    OnLevelUpdated.Broadcast(CurrentLevel);
    OnLevelUpRequested.Broadcast(CurrentLevel);
}

// ============================================================
// AFFECTED STATS FUNCTIONS
// ============================================================

void UAC_StatManager::AdjustAffectedStats(UB_Stat* Stat, double Change, E_ValueType ValueType)
{
    if (!Stat) return;

    // Get the stat's behavior modifiers
    const FStatInfo& StatInfo = Stat->StatInfo;
    const FStatBehavior& Behavior = StatInfo.StatModifiers;

    // Iterate through all stats this stat affects
    for (const auto& AffectedPair : Behavior.StatsToAffect)
    {
        const FGameplayTag& AffectedTag = AffectedPair.Key;
        const FAffectedStats& AffectedData = AffectedPair.Value;

        // Process each softcap entry
        for (const FAffectedStat& SoftcapEntry : AffectedData.SoftcapData)
        {
            // Check if current level is within range
            if (CurrentLevel >= SoftcapEntry.FromLevel && CurrentLevel <= SoftcapEntry.UntilLevel)
            {
                // Calculate the change using the modifier
                double CalculatedChange = Calculate(SoftcapEntry.Modifier, Change);

                // Determine which value type to adjust
                E_ValueType TargetValueType = SoftcapEntry.bAffectMaxValue ? E_ValueType::Max : ValueType;

                // Apply the adjustment
                if (SoftcapEntry.bAffectMaxValue)
                {
                    AdjustAffectedValue(AffectedTag, TargetValueType, CalculatedChange);
                }
                else
                {
                    AdjustAffected(AffectedTag, TargetValueType, CalculatedChange);
                }
            }
        }
    }
}

void UAC_StatManager::AdjustAffected(FGameplayTag StatTag, E_ValueType ValueType, double Change)
{
    UB_Stat* Stat = GetStat(StatTag);
    if (!IsValid(Stat)) return;

    // Apply the change based on value type
    switch (ValueType)
    {
    case E_ValueType::Current:
        Stat->ModifyStat(static_cast<float>(Change));
        break;
    case E_ValueType::Max:
        Stat->MaxValue += static_cast<float>(Change);
        break;
    case E_ValueType::Base:
        Stat->BaseValue += static_cast<float>(Change);
        break;
    default:
        break;
    }
}

void UAC_StatManager::AdjustAffectedValue(FGameplayTag StatTag, E_ValueType ValueType, double Change)
{
    UB_Stat* Stat = GetStat(StatTag);
    if (!IsValid(Stat)) return;

    // Similar to AdjustAffected but with rounded values
    int32 RoundedChange = FMath::RoundToInt(Change);

    switch (ValueType)
    {
    case E_ValueType::Current:
        Stat->ModifyStat(static_cast<float>(RoundedChange));
        break;
    case E_ValueType::Max:
        Stat->MaxValue += static_cast<float>(RoundedChange);
        break;
    case E_ValueType::Base:
        Stat->BaseValue += static_cast<float>(RoundedChange);
        break;
    default:
        break;
    }
}

double UAC_StatManager::Calculate(double Modifier, double ChangeAmount)
{
    // Switch on calculation type
    switch (CalculationType)
    {
    case E_CalculationType::Multiply:
        return ChangeAmount * Modifier;
    default:
        return ChangeAmount * Modifier;
    }
}

// ============================================================
// SAVE/LOAD FUNCTIONS
// ============================================================

void UAC_StatManager::InitializeLoadedStats(const TArray<FStatInfo>& LoadedStats)
{
    // Only process if not AI component
    if (bIsAiComponent)
    {
        return;
    }

    // For each loaded stat, find and update the active stat
    for (const FStatInfo& LoadedInfo : LoadedStats)
    {
        // Find the stat by tag
        if (UB_Stat* Stat = GetStat(LoadedInfo.Tag))
        {
            // Update the stat with loaded info
            Stat->UpdateStatInfo(LoadedInfo);
        }
    }
}

void UAC_StatManager::UpdateStatInfo(UB_Stat* Stat, const FStatInfo& NewStatInfo)
{
    if (!IsValid(Stat)) return;

    Stat->UpdateStatInfo(NewStatInfo);
}

UAC_SaveLoadManager* UAC_StatManager::GetSaveLoadComponent() const
{
    // Get from player controller
    if (APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0))
    {
        return PC->FindComponentByClass<UAC_SaveLoadManager>();
    }
    return nullptr;
}

UPDA_BaseCharacterInfo* UAC_StatManager::GetSelectedClass() const
{
    // This would get the selected character class from the game instance
    // Implementation depends on BPI_GameInstance interface
    return nullptr;
}

// ============================================================
// EVENT HANDLERS
// ============================================================

void UAC_StatManager::OnStatUpdatedHandler(UB_Stat* UpdatedStat, double Change, bool bUpdateAffectedStats, E_ValueType ValueType)
{
    // If we should update affected stats, do so
    if (bUpdateAffectedStats)
    {
        AdjustAffectedStats(UpdatedStat, Change, ValueType);
    }
}

void UAC_StatManager::OnLevelUpRequestedHandler(int32 Delta)
{
    AdjustLevel(Delta);
}
