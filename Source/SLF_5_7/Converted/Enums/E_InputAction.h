#pragma once

#include "CoreMinimal.h"
#include "E_InputAction.generated.h"

UENUM(BlueprintType)
enum class E_InputAction : uint8
{
	None UMETA(DisplayName = "-"),
	Jump UMETA(DisplayName = "Jump"),
	Dodge UMETA(DisplayName = "Dodge"),
	Block UMETA(DisplayName = "Block"),
	LightAttack UMETA(DisplayName = "Light Attack"),
	HeavyAttack UMETA(DisplayName = "Heavy Attack"),
	JumpAttack UMETA(DisplayName = "Jump Attack"),
	SpecialAttack UMETA(DisplayName = "Special Attack"),
	DrinkFlask UMETA(DisplayName = "Drink Flask")
};
