#pragma once

#include "CoreMinimal.h"
#include "E_AI_Senses.generated.h"

// Matches Blueprint E_AI_Senses exactly
// JSON values: -, Sight, Hearing
UENUM(BlueprintType)
enum class E_AI_Senses : uint8
{
	None UMETA(DisplayName = "-"),
	Sight UMETA(DisplayName = "Sight"),
	Hearing UMETA(DisplayName = "Hearing")
};
