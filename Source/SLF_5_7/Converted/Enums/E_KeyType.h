#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class E_KeyType : uint8
{
	Bool UMETA(DisplayName="Bool"),
	Class UMETA(DisplayName="Class"),
	Enum UMETA(DisplayName="Enum"),
	Float UMETA(DisplayName="Float"),
	Int UMETA(DisplayName="Int"),
	Name UMETA(DisplayName="Name"),
	Object UMETA(DisplayName="Object"),
	Rotator UMETA(DisplayName="Rotator"),
	String UMETA(DisplayName="String"),
	Vector UMETA(DisplayName="Vector"),
};
