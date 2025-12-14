// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "Structs/FDayNightInfo.h"
#include "PDA_DayNight.generated.h"


/**
 * Data Asset for Day/Night settings and query logic.
 */
UCLASS(BlueprintType)
class SLF_5_7_API UPDA_DayNight : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPDA_DayNight();

	/** List of Time Entries */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DayNight")
	TArray<FDayNightInfo> Entries;

	/** Debug flag */
	UPROPERTY(EditAnywhere, Category = "Debug")
	bool DEBUG_DEFAULT_CHECK = true;

	/**
	 * Retrieves Day/Night info for a specific time tag.
	 * @param TimeTag - The tag to search for.
	 * @param OutEntry - The found entry.
	 * @param bSuccess - Whether the entry was found.
	 */
	UFUNCTION(BlueprintCallable, Category = "DayNight")
	void GetInfoForTimeTag(FGameplayTag TimeTag, FDayNightInfo& OutEntry, bool& bSuccess);
};
