#pragma once

#include "CoreMinimal.h"
#include "E_AI_StateHandle.generated.h"

UENUM(BlueprintType)
enum class E_AI_StateHandle : uint8
{
	Current UMETA(DisplayName = "Current"),
	Previous UMETA(DisplayName = "Previous")
};
