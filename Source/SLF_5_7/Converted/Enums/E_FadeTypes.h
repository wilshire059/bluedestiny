#pragma once

#include "CoreMinimal.h"
#include "E_FadeTypes.generated.h"

// Matches Blueprint E_FadeTypes exactly
// JSON values: Fade In, Fade Out, Fade In n Out
UENUM(BlueprintType)
enum class E_FadeTypes : uint8
{
	FadeIn UMETA(DisplayName = "Fade In"),
	FadeOut UMETA(DisplayName = "Fade Out"),
	FadeInNOut UMETA(DisplayName = "Fade In n Out")
};
