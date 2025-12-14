#pragma once

#include "CoreMinimal.h"
#include "E_MovementType.generated.h"

UENUM(BlueprintType)
enum class E_MovementType : uint8
{
	Run UMETA(DisplayName = "Run"),
	Walk UMETA(DisplayName = "Walk"),
	Sprint UMETA(DisplayName = "Sprint")
};
