#pragma once

#include "CoreMinimal.h"
#include "E_NpcState.generated.h"

UENUM(BlueprintType)
enum class E_NpcState : uint8
{
	NotSpawned UMETA(DisplayName = "NotSpawned"),
	Spawned UMETA(DisplayName = "Spawned"),
	Inactive UMETA(DisplayName = "Inactive"),
	Active UMETA(DisplayName = "Active"),
	Hostile UMETA(DisplayName = "Hostile"),
	Friendly UMETA(DisplayName = "Friendly")
};
