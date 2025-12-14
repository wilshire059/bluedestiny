// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Engine/Texture2D.h"
#include "PDA_LoadingScreens.generated.h"

/**
 * Struct for Loading Screen Tips.
 */
USTRUCT(BlueprintType)
struct FLoadingScreenTip
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Loading")
	FText TipTitle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Loading")
	FText TipDescription;
};

/**
 * Data Asset for Loading Screens.
 */
UCLASS(BlueprintType)
class SLF_5_7_API UPDA_LoadingScreens : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPDA_LoadingScreens();

	/** List of Loading Screen Textures */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Loading")
	TArray<TSoftObjectPtr<UTexture2D>> Textures;

	/** List of Loading Screen Tips */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Loading")
	TArray<FLoadingScreenTip> Tips;

	/** Debug flag */
	UPROPERTY(EditAnywhere, Category = "Debug")
	bool DEBUG_DEFAULT_CHECK = true;

	/**
	 * Gets a random loading screen data (texture and tip).
	 * @param OutTexture - The selected texture.
	 * @param OutTip - The selected tip.
	 */
	UFUNCTION(BlueprintCallable, Category = "Loading")
	void GetRandomLoadingScreenData(TSoftObjectPtr<UTexture2D>& OutTexture, FLoadingScreenTip& OutTip);
};
