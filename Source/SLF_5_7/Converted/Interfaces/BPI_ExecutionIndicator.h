#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BPI_ExecutionIndicator.generated.h"

UINTERFACE(MinimalAPI, BlueprintType)
class UBPI_ExecutionIndicator : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface for Execution Indicator widgets.
 * Matches Blueprint BPI_ExecutionIndicator exactly.
 */
class SLF_5_7_API IBPI_ExecutionIndicator
{
	GENERATED_BODY()

public:
	/** Toggle execution indicator visibility (matches Blueprint signature) */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Execution")
	void ToggleExecutionIcon(bool bVisible);
};
