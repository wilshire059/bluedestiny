// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PDA_CustomSettings.generated.h"

/**
 * Data Asset for Custom Settings (e.g. Camera).
 */
UCLASS(BlueprintType)
class SLF_5_7_API UPDA_CustomSettings : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPDA_CustomSettings();

	/** Invert Camera X Axis */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
	bool InvertCamX = false;

	/** Invert Camera Y Axis */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
	bool InvertCamY = false;

	/** Camera Speed Multiplier */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
	double CamSpeed = 1.0;

	/** Debug flag */
	UPROPERTY(EditAnywhere, Category = "Debug")
	bool DEBUG_DEFAULT_CHECK = true;
};
