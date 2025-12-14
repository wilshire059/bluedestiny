#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "FDayNightInfo.generated.h"

/**
 * Struct for Day/Night Cycle Information.
 */
USTRUCT(BlueprintType)
struct SLF_5_7_API FDayNightInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DayNight")
	FGameplayTag Tag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DayNight")
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DayNight")
	double FromTime = 0.0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DayNight")
	double ToTime = 0.0;
};
