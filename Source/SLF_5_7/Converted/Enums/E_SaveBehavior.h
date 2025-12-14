#pragma once

#include "CoreMinimal.h"
#include "E_SaveBehavior.generated.h"

UENUM(BlueprintType)
enum class E_SaveBehavior : uint8
{
	None UMETA(DisplayName = "None"),
	SaveOnly UMETA(DisplayName = "Save Only"),
	SaveAndSerialize UMETA(DisplayName = "Save and Serialize"),
	LoadOnly UMETA(DisplayName = "Load Only")
};
