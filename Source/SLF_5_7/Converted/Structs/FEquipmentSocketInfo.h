#pragma once

#include "CoreMinimal.h"
#include "FEquipmentSocketInfo.generated.h"

USTRUCT(BlueprintType)
struct SLF_5_7_API FEquipmentSocketInfo
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Equipment")
	FName LeftHandSocketName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Equipment")
	FName RightHandSocketName;
};
