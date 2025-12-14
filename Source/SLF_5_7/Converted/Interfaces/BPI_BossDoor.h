#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BPI_BossDoor.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UBPI_BossDoor : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SLF_5_7_API IBPI_BossDoor
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Boss Door")
	void UnlockBossDoor();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Boss Door")
	USceneComponent* GetDeathCurrencySpawnPoint();
};
