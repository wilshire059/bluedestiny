#pragma once

#include "CoreMinimal.h"
#include "PDA_Item.h"
#include "FLootItem.generated.h"

USTRUCT(BlueprintType)
struct FLootItem
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSoftObjectPtr<UPDA_Item> Item;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Chance = 1.0f; 

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 MinAmount = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 MaxAmount = 1;

    bool operator==(const FLootItem& Other) const
    {
        return Item == Other.Item;
    }

    friend uint32 GetTypeHash(const FLootItem& Thing)
    {
        return GetTypeHash(Thing.Item);
    }
};
