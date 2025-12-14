#pragma once

#include "CoreMinimal.h"
#include "E_Progress.generated.h"

UENUM(BlueprintType)
enum class E_Progress : uint8
{
	None UMETA(DisplayName = "None"),
	InProgress UMETA(DisplayName = "In Progress"),
	Completed UMETA(DisplayName = "Completed"),
	Failed UMETA(DisplayName = "Failed"),
	Unlocked UMETA(DisplayName = "Unlocked")
};
