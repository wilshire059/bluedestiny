// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Engine/Texture2D.h"
#include "GameplayTagContainer.h"
#include "Structs/FCreditsEntry.h"
#include "Structs/FCreditsExtra.h"
#include "PDA_Credits.generated.h"


/**
 * Data Asset for Credits Sequence.
 */
UCLASS(BlueprintType)
class SLF_5_7_API UPDA_Credits : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPDA_Credits();

	/** List of Credit Entries */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Credits")
	TArray<FCreditsEntry> EntryList;

	/** List of Extra Data */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Credits")
	TArray<FCreditsExtra> ExtraData;

	/** Debug flag */
	UPROPERTY(EditAnywhere, Category = "Debug")
	bool DEBUG_DEFAULT_CHECK = true;
};
