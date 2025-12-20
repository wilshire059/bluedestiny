#pragma once

#include "CoreMinimal.h"
#include "E_Progress.generated.h"

// Matches Blueprint E_Progress exactly
// JSON values: NotStarted, InProgress, Completed
UENUM(BlueprintType)
enum class E_Progress : uint8
{
	NotStarted UMETA(DisplayName = "NotStarted"),
	InProgress UMETA(DisplayName = "InProgress"),
	Completed UMETA(DisplayName = "Completed")
};
