#pragma once

#include "CoreMinimal.h"
#include "E_AI_Senses.generated.h"

UENUM(BlueprintType)
enum class E_AI_Senses : uint8
{
	None UMETA(DisplayName = "None"),
	Sight UMETA(DisplayName = "Sight"),
	Hearing UMETA(DisplayName = "Hearing"),
	Damage UMETA(DisplayName = "Damage"),
	Touch UMETA(DisplayName = "Touch")
};
