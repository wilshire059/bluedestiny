#pragma once

#include "CoreMinimal.h"
#include "E_AttackPower.generated.h"

UENUM(BlueprintType)
enum class E_AttackPower : uint8
{
	Physical UMETA(DisplayName = "Physical"),
	Magic UMETA(DisplayName = "Magic"),
	Fire UMETA(DisplayName = "Fire"),
	Frost UMETA(DisplayName = "Frost"),
	Lightning UMETA(DisplayName = "Lightning"),
	Holy UMETA(DisplayName = "Holy")
};
