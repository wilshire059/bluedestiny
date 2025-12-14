// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PDA_Calculations.generated.h"

/**
 * Calculation Types enum.
 */
UENUM(BlueprintType)
enum class E_CalculationType : uint8
{
	Multiply UMETA(DisplayName = "Multiply"),
	// Add other types as needed
};

/**
 * Data Asset for Calculations.
 */
UCLASS(BlueprintType)
class SLF_5_7_API UPDA_Calculations : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPDA_Calculations();

	/** Type of calculation to perform */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings")
	E_CalculationType CalculationType;

	/** Debug flag */
	UPROPERTY(EditAnywhere, Category = "Debug")
	bool DEBUG_DEFAULT_CHECK = true;

	/**
	 * Calculates the output change based on modifier and input change amount.
	 * @param Modifier - The modifier value.
	 * @param ChangeAmount - The input change amount.
	 * @param OutChange - The calculated output change.
	 */
	UFUNCTION(BlueprintCallable, Category = "Calculation")
	void Calculate(double Modifier, double ChangeAmount, double& OutChange);
};
