#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "FReplenishInfo.generated.h"

class UPDA_Item;

/**
 * Information about items and stats to replenish (e.g., at resting points)
 */
USTRUCT(BlueprintType)
struct SLF_5_7_API FReplenishInfo
{
    GENERATED_BODY()

    /** Items that should be replenished */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Replenish")
    TArray<TObjectPtr<UPDA_Item>> ItemsToReplenish;

    /** Stats that should be replenished (identified by gameplay tags) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Replenish")
    TArray<FGameplayTag> StatsToReplenish;

    FReplenishInfo()
    {
    }
};
