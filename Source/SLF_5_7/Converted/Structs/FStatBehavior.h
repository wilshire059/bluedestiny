#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "FAffectedStats.h"
#include "FStatBehavior.generated.h"

USTRUCT(BlueprintType)
struct SLF_5_7_API FStatBehavior
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Stats")
	TMap<FGameplayTag, FAffectedStats> StatsToAffect;
};
