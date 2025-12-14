#pragma once

#include "CoreMinimal.h"
#include "E_Direction.generated.h"

UENUM(BlueprintType)
enum class E_Direction : uint8
{
	None UMETA(DisplayName = "None"),
	Forward UMETA(DisplayName = "Forward"),
	Backward UMETA(DisplayName = "Backward"),
	Left UMETA(DisplayName = "Left"),
	Right UMETA(DisplayName = "Right"),
	ForwardLeft UMETA(DisplayName = "Forward Left"),
	ForwardRight UMETA(DisplayName = "Forward Right"),
	BackwardLeft UMETA(DisplayName = "Backward Left"),
	BackwardRight UMETA(DisplayName = "Backward Right")
};
