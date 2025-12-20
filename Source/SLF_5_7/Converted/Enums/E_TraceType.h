#pragma once

#include "CoreMinimal.h"
#include "E_TraceType.generated.h"

// Matches Blueprint E_TraceType exactly
// JSON values: Right Hand, Left Hand, Both
UENUM(BlueprintType)
enum class E_TraceType : uint8
{
	RightHand UMETA(DisplayName = "Right Hand"),
	LeftHand UMETA(DisplayName = "Left Hand"),
	Both UMETA(DisplayName = "Both")
};
