#pragma once

#include "CoreMinimal.h"
#include "E_VendorType.generated.h"

UENUM(BlueprintType)
enum class E_VendorType : uint8
{
	Buy UMETA(DisplayName = "Buy"),
	Sell UMETA(DisplayName = "Sell")
};
