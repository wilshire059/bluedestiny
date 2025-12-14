// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Animation/AnimMontage.h"
#include "InstancedStruct.h"
#include "PDA_AI_Ability.generated.h"

/**
 * Data Asset for AI Abilities.
 */
UCLASS(BlueprintType)
class SLF_5_7_API UPDA_AI_Ability : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPDA_AI_Ability();

	/** Montage to play for this ability */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings")
	TSoftObjectPtr<UAnimMontage> Montage;

	/** Score or weight for selecting this ability */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings")
	double Score = 1.0;

	/** Cooldown duration */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings")
	double Cooldown = 0.0;

	/** Conditions/Rules for this ability */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings")
	TArray<FInstancedStruct> AiRules;
};
