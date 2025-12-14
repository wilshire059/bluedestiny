// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Animation/AnimationAsset.h"
#include "PDA_CombatReactionAnimData_Player.generated.h"

/**
 * Data Asset for Player Combat Reaction Animations.
 */
UCLASS(BlueprintType)
class SLF_5_7_API UPDA_CombatReactionAnimData_Player : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPDA_CombatReactionAnimData_Player();

	/** Poise Break Animation (or Montage) */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Reactions")
	TSoftObjectPtr<UAnimationAsset> PoiseBreak;

	/** Debug flag */
	UPROPERTY(EditAnywhere, Category = "Debug")
	bool DEBUG_DEFAULT_CHECK = true;
};
