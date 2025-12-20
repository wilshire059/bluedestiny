#pragma once

#include "CoreMinimal.h"
#include "Enums/E_Progress.h"
#include "FDialogRequirement.generated.h"

class UDataTable;

/**
 * Dialog requirement data.
 */
USTRUCT(BlueprintType)
struct SLF_5_7_API FDialogRequirement
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialog")
	E_Progress RequiredProgress = E_Progress::NotStarted;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialog")
	TSoftObjectPtr<UDataTable> DialogTable;
};
