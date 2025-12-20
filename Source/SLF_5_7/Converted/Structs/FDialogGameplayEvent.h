#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "FDialogGameplayEvent.generated.h"

// Forward declare FInstancedStruct to avoid deprecated StructUtils dependency
struct FInstancedStruct;

USTRUCT(BlueprintType)
struct SLF_5_7_API FDialogGameplayEvent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialog")
	FGameplayTag EventTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialog")
	FGameplayTag AdditionalTag;

	// CustomData is stored as raw bytes for now (StructUtils deprecated in UE5.5+)
	// Full implementation would use FInstancedStruct when the module dependency is resolved
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialog")
	TArray<uint8> CustomDataBytes;
};
