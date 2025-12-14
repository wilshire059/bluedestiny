// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PDA_MovementSpeedData.generated.h"

/**
 * Data Asset for Movement Speeds.
 */
UCLASS(BlueprintType)
class SLF_5_7_API UPDA_MovementSpeedData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPDA_MovementSpeedData();

	/** Walk Speed */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	double WalkSpeed = 200.0;

	/** Run Speed */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	double RunSpeed = 600.0;

	/** Sprint Speed */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	double SprintSpeed = 900.0;

	/** Debug flag */
	UPROPERTY(EditAnywhere, Category = "Debug")
	bool DEBUG_DEFAULT_CHECK = true;
};
