#include "AC_LootDropManager.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/StreamableManager.h"
#include "Engine/AssetManager.h"

UAC_LootDropManager::UAC_LootDropManager()
{
    PrimaryComponentTick.bCanEverTick = false;
}

bool UAC_LootDropManager::IsOverrideItemValid() const
{
    // Check if Override Item stores a valid Soft Pointer or similar logic. 
    // JSON node N15 accessed OverrideItem.Item (PDA_Item).
    return !OverrideItem.Item.IsNull();
}

void UAC_LootDropManager::PickItem()
{
    // 1. Check Override
    if (IsOverrideItemValid())
    {
        OnItemReadyForSpawn.Broadcast(OverrideItem);
        return;
    }

    // 2. Load LootTable if valid
    if (LootTable.IsNull())
    {
        return;
    }

    // Async Load
    FStreamableManager& Streamable = UAssetManager::GetStreamableManager();
    Streamable.RequestAsyncLoad(LootTable.ToSoftObjectPath(), FStreamableDelegate::CreateLambda([this]()
    {
        if (UDataTable* Table = LootTable.Get())
        {
            FLootItem SelectedItem = GetRandomItemFromTable(Table);
            OnItemReadyForSpawn.Broadcast(SelectedItem);
        }
    }));
}

FLootItem UAC_LootDropManager::GetRandomItemFromTable(UDataTable* Table)
{
    FLootItem ResultItem;
    if (!Table) return ResultItem;

    TMap<FLootItem, double> LocalItems; // Key: Item, Value: Weight
    double TotalWeight = 0.0;

    // First Pass: Accumulate Weights
    // Iterate all rows
    FString Context;
    for (auto& RowName : Table->GetRowNames())
    {
        if (FWeightedLoot* Row = Table->FindRow<FWeightedLoot>(RowName, Context))
        {
            LocalItems.Add(Row->Item, Row->Weight);
            TotalWeight += Row->Weight;
        }
    }

    // Pick Random
    double RandomValue = UKismetMathLibrary::RandomFloatInRange(0.0, TotalWeight);
    double CurrentWeight = 0.0;

    // Second Pass: Find Item
    for (const auto& Elem : LocalItems)
    {
        CurrentWeight += Elem.Value;
        if (CurrentWeight >= RandomValue)
        {
            return Elem.Key;
        }
    }
    
    // Fallback (e.g. rounding error?) return last item or empty
    if (LocalItems.Num() > 0)
    {
        // Return first or last logic? JSON had Return in Loop.
        // Assuming we return last hit if something weird happens, or empty.
    }

    return ResultItem;
}
