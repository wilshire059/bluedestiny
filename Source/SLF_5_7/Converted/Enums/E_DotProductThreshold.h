#pragma once

#include "CoreMinimal.h"
#include "E_DotProductThreshold.generated.h"

UENUM(BlueprintType)
enum class E_DotProductThreshold : uint8
{
	Low UMETA(DisplayName = "Low"),
	Medium UMETA(DisplayName = "Medium"),
	High UMETA(DisplayName = "High"),
	Generous UMETA(DisplayName = "Generous")
};
