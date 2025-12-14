// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PDA_MainMenuData.generated.h"

class UObject;

/**
 * Data Asset for Main Menu Settings.
 */
UCLASS(BlueprintType)
class SLF_5_7_API UPDA_MainMenuData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPDA_MainMenuData();

	/** Asset to use for loading screen (Widget Class or similar) */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MainMenu")
	TSoftClassPtr<UObject> LoadingScreenAsset;

	/** Minimum additional wait time */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MainMenu")
	double AdditionalWaitMin = 0.0;

	/** Maximum additional wait time */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MainMenu")
	double AdditionalWaitMax = 0.0;

	/** Whether to remove widget on finish */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MainMenu")
	bool bRemoveOnFinish = false;

	/** Default level to load */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MainMenu")
	TSoftObjectPtr<UWorld> DefaultLevelToLoad;

	/** Debug flag */
	UPROPERTY(EditAnywhere, Category = "Debug")
	bool DEBUG_DEFAULT_CHECK = true;
};
