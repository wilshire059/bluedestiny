#pragma once

#include "CoreMinimal.h"
#include "FCardinalData.generated.h"

USTRUCT(BlueprintType)
struct SLF_5_7_API FCardinalData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString UIDisplayText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double Value = 0.0;
};
