#pragma once

#include "CoreMinimal.h"
#include "E_AI_BossEncounterType.generated.h"

UENUM(BlueprintType)
enum class E_AI_BossEncounterType : uint8
{
	Perception UMETA(DisplayName = "Perception"),
	CollisionTrigger UMETA(DisplayName = "Collision Trigger"),
	OnDamaged UMETA(DisplayName = "On Damaged")
};
