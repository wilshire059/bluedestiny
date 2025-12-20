#pragma once

#include "CoreMinimal.h"
#include "E_AI_States.generated.h"

// Matches Blueprint E_AI_States exactly
UENUM(BlueprintType)
enum class E_AI_States : uint8
{
	Idle UMETA(DisplayName = "Idle"),
	RandomRoam UMETA(DisplayName = "Random Roam"),
	Patrolling UMETA(DisplayName = "Patrolling"),
	Investigating UMETA(DisplayName = "Investigating"),
	Combat UMETA(DisplayName = "Combat"),
	PoiseBroken UMETA(DisplayName = "Poise Broken"),
	Uninterruptable UMETA(DisplayName = "Uninterruptable"),
	OutOfBounds UMETA(DisplayName = "Out of Bounds")
};
