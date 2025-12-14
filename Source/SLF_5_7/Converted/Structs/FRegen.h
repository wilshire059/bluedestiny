#pragma once

#include "CoreMinimal.h"
#include "FRegen.generated.h"

USTRUCT(BlueprintType)
struct SLF_5_7_API FRegen
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Stats")
	bool bCanRegenerate = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Stats")
	double RegenInterval = 1.0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Stats")
	double RegenPercent = 0.0;
};
