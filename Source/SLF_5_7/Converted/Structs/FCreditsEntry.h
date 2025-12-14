#pragma once

#include "CoreMinimal.h"
#include "FCreditsEntry.generated.h"

/**
 * Struct for Credits Entry.
 */
USTRUCT(BlueprintType)
struct SLF_5_7_API FCreditsEntry
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Credits")
	FText Title;

	/** Map of Name to Role or Subtitle info */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Credits")
	TMap<FString, FText> Subtitle;
};
