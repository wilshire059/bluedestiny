#pragma once

#include "CoreMinimal.h"
#include "E_InventorySlotType.generated.h"

UENUM(BlueprintType)
enum class E_InventorySlotType : uint8
{
    InventorySlot UMETA(DisplayName = "Inventory Slot"),
    StorageSlot UMETA(DisplayName = "Storage Slot")
};
