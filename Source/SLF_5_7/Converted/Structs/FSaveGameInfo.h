#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "FSaveGameInfo.generated.h"

/**
 * Container for save game data.
 */
USTRUCT(BlueprintType)
struct SLF_5_7_API FSaveGameInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save")
	FString SlotName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save")
	FDateTime SaveTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save")
	FGameplayTag LastLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save")
	int32 TotalPlayTime = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save")
	int32 CharacterLevel = 1;
};
