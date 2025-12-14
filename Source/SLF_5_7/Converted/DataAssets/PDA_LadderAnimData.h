// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Animation/AnimationAsset.h"
#include "PDA_LadderAnimData.generated.h"

/**
 * Data Asset for Ladder Animations.
 */
UCLASS(BlueprintType)
class SLF_5_7_API UPDA_LadderAnimData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPDA_LadderAnimData();

	/** Animation for climbing up */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ladder")
	TSoftObjectPtr<UAnimationAsset> ClimbUp;

	/** Animation for climbing down */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ladder")
	TSoftObjectPtr<UAnimationAsset> ClimbDown;

	/** Animation for climbing out at top */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ladder")
	TSoftObjectPtr<UAnimationAsset> ClimbOutAtTop;

	/** Animation for climbing in from top */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ladder")
	TSoftObjectPtr<UAnimationAsset> ClimbInFromTop;

	/** Debug flag */
	UPROPERTY(EditAnywhere, Category = "Debug")
	bool DEBUG_DEFAULT_CHECK = true;
};
