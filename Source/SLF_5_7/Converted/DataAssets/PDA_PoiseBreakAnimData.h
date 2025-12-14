// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Animation/AnimationAsset.h"
#include "PDA_PoiseBreakAnimData.generated.h"

/**
 * Data Asset for Poise Break Animations (Start and Loop).
 */
UCLASS(BlueprintType)
class SLF_5_7_API UPDA_PoiseBreakAnimData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPDA_PoiseBreakAnimData();

	/** Start animation for poise break */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PoiseBreak")
	TSoftObjectPtr<UAnimationAsset> PoiseBreak_Start;

	/** Loop animation for poise break */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PoiseBreak")
	TSoftObjectPtr<UAnimationAsset> PoiseBreak_Loop;

	/** Debug flag */
	UPROPERTY(EditAnywhere, Category = "Debug")
	bool DEBUG_DEFAULT_CHECK = true;
};
