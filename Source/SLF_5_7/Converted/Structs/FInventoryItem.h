#pragma once

#include "PDA_Item.h"
#include "FInventoryItem.generated.h"

USTRUCT(BlueprintType)
struct SLF_5_7_API FInventoryItem
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
    TObjectPtr<UPDA_Item> ItemAsset;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
    int32 Amount;

    FInventoryItem()
        : ItemAsset(nullptr), Amount(0)
    {}

    bool operator==(const FInventoryItem& Other) const
    {
        return ItemAsset == Other.ItemAsset;
    }
};
