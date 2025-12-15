#pragma once

#include "CoreMinimal.h"
#include "Shakes/LegacyCameraShake.h"
#include "CS_Seq_Handheld.generated.h"

/**
 * Perlin noise based camera shake for cinematic sequences
 * This shake provides a smooth, handheld camera feel
 */
UCLASS()
class SLF_5_7_API UCS_Seq_Handheld : public ULegacyCameraShake
{
	GENERATED_BODY()

public:
	UCS_Seq_Handheld();
};
