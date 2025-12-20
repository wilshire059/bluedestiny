#pragma once

#include "CoreMinimal.h"
#include "E_ActionWeaponSlot.generated.h"

// Matches Blueprint E_ActionWeaponSlot exactly
// JSON values: Null, Right, Left, Dual
UENUM(BlueprintType)
enum class E_ActionWeaponSlot : uint8
{
	Null UMETA(DisplayName = "Null"),
	Right UMETA(DisplayName = "Right"),
	Left UMETA(DisplayName = "Left"),
	Dual UMETA(DisplayName = "Dual")
};
