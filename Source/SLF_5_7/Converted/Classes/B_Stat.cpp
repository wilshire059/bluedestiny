#include "B_Stat.h"
#include "Engine/World.h"
#include "TimerManager.h"

UB_Stat::UB_Stat()
{
    BaseValue = 100.0f;
    MaxValue = 100.0f;
    CurrentValue = 100.0f;
}

UWorld* UB_Stat::GetWorld() const
{
    // Try to get world from Outer if it's an Actor or Component
    if (const UObject* Outer = GetOuter())
    {
        return Outer->GetWorld();
    }
    return nullptr;
}

void UB_Stat::Initialize(float InBaseValue, float InMaxValue)
{
    BaseValue = InBaseValue;
    MaxValue = InMaxValue;
    CurrentValue = MaxValue; // Default to max?
    OnStatChanged.Broadcast(CurrentValue, MaxValue, GetPercent());
    
    if (RegenConfig.bCanRegenerate)
    {
        ToggleRegen(true);
    }
}

void UB_Stat::ModifyStat(float Amount)
{
    float OldValue = CurrentValue;
    CurrentValue = FMath::Clamp(CurrentValue + Amount, 0.0f, MaxValue);
    
    if (!FMath::IsNearlyEqual(OldValue, CurrentValue))
    {
        OnStatChanged.Broadcast(CurrentValue, MaxValue, GetPercent());
    }
}

void UB_Stat::SetCurrentValue(float NewValue)
{
    ModifyStat(NewValue - CurrentValue);
}

float UB_Stat::GetPercent() const
{
    if (MaxValue <= 0.0f) return 0.0f;
    return CurrentValue / MaxValue;
}

void UB_Stat::ToggleRegen(bool bEnable)
{
    UWorld* World = GetWorld();
    if (!World) return;

    if (bEnable)
    {
        if (!World->GetTimerManager().IsTimerActive(RegenTimerHandle))
        {
            World->GetTimerManager().SetTimer(RegenTimerHandle, this, &UB_Stat::OnRegenTick, RegenConfig.RegenInterval, true);
        }
    }
    else
    {
        World->GetTimerManager().ClearTimer(RegenTimerHandle);
    }
}

void UB_Stat::OnRegenTick()
{
    if (CurrentValue < MaxValue)
    {
        float Amount = RegenConfig.RegenPercent * MaxValue; // Assuming percent
        ModifyStat(Amount);
    }
}

void UB_Stat::UpdateStatInfo(const FStatInfo& NewStatInfo)
{
    StatInfo = NewStatInfo;

    // Apply the stat info values
    StatTag = NewStatInfo.Tag;
    CurrentValue = NewStatInfo.Value;
    MaxValue = NewStatInfo.MaxValue;

    // Broadcast update
    OnStatUpdated.Broadcast(this, 0.0, false, E_ValueType::Current);
    OnStatChanged.Broadcast(CurrentValue, MaxValue, GetPercent());
}

FStatInfo UB_Stat::GetStatInfo() const
{
    FStatInfo Info;
    Info.Tag = StatTag;
    Info.Value = CurrentValue;
    Info.MaxValue = MaxValue;
    return Info;
}
