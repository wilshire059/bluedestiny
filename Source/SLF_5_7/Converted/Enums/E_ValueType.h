#pragma once

#include "CoreMinimal.h"
#include "E_ValueType.generated.h"

// Blueprint has: Current Value, Max Value
// C++ extends with additional modifiers for stat system
UENUM(BlueprintType)
enum class E_ValueType : uint8
{
	CurrentValue UMETA(DisplayName = "Current Value"),  // Blueprint index 0
	MaxValue UMETA(DisplayName = "Max Value"),          // Blueprint index 1
	// Extended for C++ stat system:
	Current UMETA(DisplayName = "Current"),
	Max UMETA(DisplayName = "Max"),
	Base UMETA(DisplayName = "Base"),
	Flat UMETA(DisplayName = "Flat"),
	Percentage UMETA(DisplayName = "Percentage")
};
