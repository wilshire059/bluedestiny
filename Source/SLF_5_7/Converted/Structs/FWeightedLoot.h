#pragma once

#include "CoreMinimal.h"
#include "FLootItem.h"
#include "Engine/DataTable.h"
#include "FWeightedLoot.generated.h"

USTRUCT(BlueprintType)
struct FWeightedLoot : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Loot")
    FLootItem Item;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Loot")
    double Weight;

    FWeightedLoot()
        : Weight(1.0)
    {}
};
