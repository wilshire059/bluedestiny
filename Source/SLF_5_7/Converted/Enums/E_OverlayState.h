#pragma once

#include "CoreMinimal.h"
#include "E_OverlayState.generated.h"

UENUM(BlueprintType)
enum class E_OverlayState : uint8
{
    Unarmed UMETA(DisplayName = "Unarmed"),
    Shield UMETA(DisplayName = "Shield"),
    OneHanded UMETA(DisplayName = "OneHanded"),
    TwoHanded UMETA(DisplayName = "TwoHanded"),
    DualWield UMETA(DisplayName = "DualWield")
};
