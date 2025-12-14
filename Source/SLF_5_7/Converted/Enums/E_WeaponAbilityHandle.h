#pragma once

#include "CoreMinimal.h"
#include "E_WeaponAbilityHandle.generated.h"

UENUM(BlueprintType)
enum class E_WeaponAbilityHandle : uint8
{
	RightHand UMETA(DisplayName = "Right Hand"),
	LeftHand UMETA(DisplayName = "Left Hand")
};
