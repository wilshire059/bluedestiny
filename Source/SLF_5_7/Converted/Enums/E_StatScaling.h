#pragma once

#include "CoreMinimal.h"
#include "E_StatScaling.generated.h"

UENUM(BlueprintType)
enum class E_StatScaling : uint8
{
	S UMETA(DisplayName = "S"),
	A UMETA(DisplayName = "A"),
	B UMETA(DisplayName = "B"),
	C UMETA(DisplayName = "C"),
	D UMETA(DisplayName = "D"),
	E UMETA(DisplayName = "E")
};
