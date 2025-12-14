#pragma once

#include "CoreMinimal.h"
#include "E_InventoryAmountedActionType.generated.h"

UENUM(BlueprintType)
enum class E_InventoryAmountedActionType : uint8
{
	Drop,
	Split,
	// Add others if needed
};
