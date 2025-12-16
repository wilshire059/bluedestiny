#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "FEquipmentStat.generated.h"

USTRUCT(BlueprintType)
struct FEquipmentStat
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag StatTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double Delta = 0.0;
};
