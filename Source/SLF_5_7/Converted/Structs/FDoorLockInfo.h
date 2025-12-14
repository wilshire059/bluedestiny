#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "FDoorLockInfo.generated.h"

USTRUCT(BlueprintType)
struct SLF_5_7_API FDoorLockInfo
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Door")
	bool bIsLocked = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Door")
	TMap<FGameplayTag, int32> RequiredItemAmount;
};
