#pragma once

#include "CoreMinimal.h"
#include "FDialogProgress.generated.h"

/**
 * Dialog progress tracking.
 */
USTRUCT(BlueprintType)
struct SLF_5_7_API FDialogProgress
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialog")
	int32 CurrentIndex = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialog")
	bool bCompleted = false;
};
