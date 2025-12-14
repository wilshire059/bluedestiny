#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class E_SettingEntry : uint8
{
	DropDown UMETA(DisplayName="Drop Down"),
	SingleButton UMETA(DisplayName="Single Button"),
	DoubleButton UMETA(DisplayName="Double Button"),
	Slider UMETA(DisplayName="Slider"),
	InputKeySelector UMETA(DisplayName="Input Key Selector"),
};
