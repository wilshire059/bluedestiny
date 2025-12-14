#pragma once

#include "CoreMinimal.h"
#include "E_ExecutionType.generated.h"

UENUM(BlueprintType)
enum class E_ExecutionType : uint8
{
	None UMETA(DisplayName = "-"),
	Backstab UMETA(DisplayName = "Backstab"),
	Execution UMETA(DisplayName = "Execution")
};
