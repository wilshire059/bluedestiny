#pragma once

#include "CoreMinimal.h"
#include "E_DebugWindowScaleType.generated.h"

UENUM(BlueprintType)
enum class E_DebugWindowScaleType : uint8
{
	None UMETA(DisplayName = "-"),
	CornerRight UMETA(DisplayName = "Corner Right"),
	CornerLeft UMETA(DisplayName = "Corner Left"),
	Right UMETA(DisplayName = "Right"),
	Left UMETA(DisplayName = "Left"),
	Bottom UMETA(DisplayName = "Bottom")
};
