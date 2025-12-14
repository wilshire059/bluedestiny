#pragma once

#include "CoreMinimal.h"
#include "E_AI_StrafeLocations.generated.h"

UENUM(BlueprintType)
enum class E_AI_StrafeLocations : uint8
{
	Back UMETA(DisplayName = "Back"),
	Left UMETA(DisplayName = "Left"),
	Right UMETA(DisplayName = "Right")
};
