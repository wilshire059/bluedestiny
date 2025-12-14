#pragma once

#include "CoreMinimal.h"
#include "E_EnclosureLevel.generated.h"

UENUM(BlueprintType)
enum class E_EnclosureLevel : uint8
{
	Closed UMETA(DisplayName = "Closed"),
	Partial UMETA(DisplayName = "Partial"),
	Open UMETA(DisplayName = "Open")
};
