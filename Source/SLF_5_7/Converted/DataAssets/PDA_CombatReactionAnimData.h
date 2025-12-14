// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Animation/AnimationAsset.h"
#include "PDA_CombatReactionAnimData.generated.h"

/**
 * Data Asset for Combat Reaction Animations (Hit, Death).
 */
UCLASS(BlueprintType)
class SLF_5_7_API UPDA_CombatReactionAnimData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPDA_CombatReactionAnimData();

	/** Animation to play on hit */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Reactions")
	TSoftObjectPtr<UAnimationAsset> HitReactions;

	/** Animation to play on death */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Reactions")
	TSoftObjectPtr<UAnimationAsset> Death;

	/** Debug flag */
	UPROPERTY(EditAnywhere, Category = "Debug")
	bool DEBUG_DEFAULT_CHECK = true;
};
