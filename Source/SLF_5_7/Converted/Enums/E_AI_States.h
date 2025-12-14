#pragma once

#include "CoreMinimal.h"
#include "E_AI_States.generated.h"

UENUM(BlueprintType)
enum class E_AI_States : uint8
{
	Idle UMETA(DisplayName = "Idle"),
	Patrol UMETA(DisplayName = "Patrol"),
	Chase UMETA(DisplayName = "Chase"),
	Combat UMETA(DisplayName = "Combat"),
	Investigate UMETA(DisplayName = "Investigate"),
	Stagger UMETA(DisplayName = "Stagger"),
	Dead UMETA(DisplayName = "Dead"),
	Disabled UMETA(DisplayName = "Disabled"),
	Reset UMETA(DisplayName = "Reset")
};

