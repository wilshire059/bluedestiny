#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "InputCoreTypes.h"
#include "BFL_Helper.generated.h"

class UInputMappingContext;
class UInputAction;

/**
 * Blueprint Function Library with helper utilities for the Soulslike Framework
 */
UCLASS()
class SLF_5_7_API UBFL_Helper : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	 * Get the keys mapped to a specific Input Action within an Input Mapping Context
	 * @param InputMapping The input mapping context to search
	 * @param TargetIA The input action to find keys for
	 * @return Array of keys mapped to the input action
	 */
	UFUNCTION(BlueprintCallable, Category = "Input|Helper")
	static TArray<FKey> GetKeysForIA(UInputMappingContext* InputMapping, UInputAction* TargetIA);
};
