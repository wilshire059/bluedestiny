#pragma once

#include "CoreMinimal.h"
#include "E_StrafeMethod.generated.h"

UENUM(BlueprintType)
enum class E_StrafeMethod : uint8
{
	None UMETA(DisplayName = "None"),
	Left UMETA(DisplayName = "Left"),
	Right UMETA(DisplayName = "Right"),
	Back UMETA(DisplayName = "Back"),
	Random UMETA(DisplayName = "Random")
};
