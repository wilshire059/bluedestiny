#pragma once

#include "CoreMinimal.h"
#include "E_InventoryAmountedActionType.generated.h"

// Matches Blueprint E_InventoryAmountedActionType exactly
// JSON values: Leave Amount, Discard Amount, Store Amount, Retrieve Amount
UENUM(BlueprintType)
enum class E_InventoryAmountedActionType : uint8
{
	LeaveAmount UMETA(DisplayName = "Leave Amount"),
	DiscardAmount UMETA(DisplayName = "Discard Amount"),
	StoreAmount UMETA(DisplayName = "Store Amount"),
	RetrieveAmount UMETA(DisplayName = "Retrieve Amount")
};
