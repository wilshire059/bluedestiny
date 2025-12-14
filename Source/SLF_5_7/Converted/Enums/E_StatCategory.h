#pragma once

#include "CoreMinimal.h"
#include "E_StatCategory.generated.h"

UENUM(BlueprintType)
enum class E_StatCategory : uint8
{
	None UMETA(DisplayName = "None"),
	Primary UMETA(DisplayName = "Primary"),
	Secondary UMETA(DisplayName = "Secondary"),
	Attack UMETA(DisplayName = "Attack"),
	Magic UMETA(DisplayName = "Magic"),
	Defense UMETA(DisplayName = "Defense"),
	Misc UMETA(DisplayName = "Misc")
};
