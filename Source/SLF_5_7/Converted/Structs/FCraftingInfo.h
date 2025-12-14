#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "FCraftingInfo.generated.h"

USTRUCT(BlueprintType)
struct SLF_5_7_API FCraftingInfo
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting")
    bool bCanBeCrafted = false;

    /** Map of Required Item Tag to Quantity */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting")
    TMap<FGameplayTag, int32> RequiredItems;
};
