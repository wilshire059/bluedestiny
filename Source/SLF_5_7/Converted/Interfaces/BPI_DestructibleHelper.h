#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BPI_DestructibleHelper.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UBPI_DestructibleHelper : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SLF_5_7_API IBPI_DestructibleHelper
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Destructible")
	void DisableChaosDestroy();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Destructible")
	void EnableChaosDestroy();
};
