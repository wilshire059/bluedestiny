#pragma once

#include "CoreMinimal.h"
#include "E_TraceType.generated.h"

UENUM(BlueprintType)
enum class E_TraceType : uint8
{
	None UMETA(DisplayName = "None"),
	Sphere UMETA(DisplayName = "Sphere"),
	Capsule UMETA(DisplayName = "Capsule"),
	Box UMETA(DisplayName = "Box"),
	Line UMETA(DisplayName = "Line")
};
