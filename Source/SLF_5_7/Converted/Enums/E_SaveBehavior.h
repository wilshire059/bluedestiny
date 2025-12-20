#pragma once

#include "CoreMinimal.h"
#include "E_SaveBehavior.generated.h"

// Matches Blueprint E_SaveBehavior exactly
// JSON values: Trigger Autosave Timer, Save Instantly
UENUM(BlueprintType)
enum class E_SaveBehavior : uint8
{
	TriggerAutosaveTimer UMETA(DisplayName = "Trigger Autosave Timer"),
	SaveInstantly UMETA(DisplayName = "Save Instantly")
};
