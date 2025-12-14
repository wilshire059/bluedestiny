#pragma once

#include "CoreMinimal.h"
#include "E_HitReactType.generated.h"

UENUM(BlueprintType)
enum class E_HitReactType : uint8
{
	None UMETA(DisplayName = "-"),
	Montage UMETA(DisplayName = "Montage"),
	IK UMETA(DisplayName = "IK"),
	Both UMETA(DisplayName = "Both")
};
