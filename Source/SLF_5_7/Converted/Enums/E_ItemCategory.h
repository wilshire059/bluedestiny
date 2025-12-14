#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class E_ItemCategory : uint8
{
	None UMETA(DisplayName="-"),
	Tools UMETA(DisplayName="Tools"),
	Crafting UMETA(DisplayName="Crafting"),
	Bolstering UMETA(DisplayName="Bolstering"),
	KeyItems UMETA(DisplayName="Key Items"),
	Abilities UMETA(DisplayName="Abilities"),
	Weapons UMETA(DisplayName="Weapons"),
	Shields UMETA(DisplayName="Shields"),
	Armor UMETA(DisplayName="Armor"),
};
