#pragma once

#include "CoreMinimal.h"
#include "E_Direction.generated.h"

// Matches Blueprint E_Direction exactly
// JSON values: Idle, Fwd, Fwd Left, Fwd Right, Left, Right, Bwd, Bwd Left, Bwd Right
UENUM(BlueprintType)
enum class E_Direction : uint8
{
	Idle UMETA(DisplayName = "Idle"),
	Fwd UMETA(DisplayName = "Fwd"),
	FwdLeft UMETA(DisplayName = "Fwd Left"),
	FwdRight UMETA(DisplayName = "Fwd Right"),
	Left UMETA(DisplayName = "Left"),
	Right UMETA(DisplayName = "Right"),
	Bwd UMETA(DisplayName = "Bwd"),
	BwdLeft UMETA(DisplayName = "Bwd Left"),
	BwdRight UMETA(DisplayName = "Bwd Right")
};
