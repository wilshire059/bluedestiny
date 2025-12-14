#pragma once

#include "CoreMinimal.h"
#include "E_LightningMode.generated.h"

UENUM(BlueprintType)
enum class E_LightningMode : uint8
{
	ExteriorLightning UMETA(DisplayName = "Exterior Lightning"),
	InteriorLightning UMETA(DisplayName = "Interior Lightning")
};
