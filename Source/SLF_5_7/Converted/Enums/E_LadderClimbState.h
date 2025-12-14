#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class E_LadderClimbState : uint8
{
	None UMETA(DisplayName="None"),
	ClimbLoop UMETA(DisplayName="Climb Loop"),
	ClimbOutFromTop UMETA(DisplayName="Climb Out From Top"),
	ClimbIntoLadderFromTop UMETA(DisplayName="Climb Into Ladder From Top"),
};
