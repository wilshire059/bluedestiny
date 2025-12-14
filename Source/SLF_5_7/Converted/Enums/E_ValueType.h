#pragma once

#include "CoreMinimal.h"
#include "E_ValueType.generated.h"

UENUM(BlueprintType)
enum class E_ValueType : uint8
{
	Current UMETA(DisplayName = "Current"),
	CurrentValue UMETA(DisplayName = "Current Value"),
	Base UMETA(DisplayName = "Base"),
	Max UMETA(DisplayName = "Max"),
	Override UMETA(DisplayName = "Override"),
	Flat UMETA(DisplayName = "Flat"),
	Percentage UMETA(DisplayName = "Percentage")
};

