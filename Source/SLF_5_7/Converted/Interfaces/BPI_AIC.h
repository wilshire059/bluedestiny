#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BPI_AIC.generated.h"

UINTERFACE(MinimalAPI, BlueprintType)
class UBPI_AIC : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface for AI Controllers.
 */
class SLF_5_7_API IBPI_AIC
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AI")
	AActor* GetCurrentTarget();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AI")
	void SetCurrentTarget(AActor* NewTarget);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AI")
	void ClearTarget();
};
