#pragma once

#include "CoreMinimal.h"
#include "E_ActionWeaponSlot.generated.h"

UENUM(BlueprintType)
enum class E_ActionWeaponSlot : uint8
{
	None UMETA(DisplayName = "None"),
	RightHand UMETA(DisplayName = "Right Hand"),
	LeftHand UMETA(DisplayName = "Left Hand"),
	TwoHand UMETA(DisplayName = "Two Hand"),
    MatchActiveHand UMETA(DisplayName = "Match Active Hand")
};
