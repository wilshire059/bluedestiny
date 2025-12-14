#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Animation/AnimationAsset.h"
#include "Animation/AnimMontage.h"
#include "GameplayTagContainer.h"
#include "PDA_ExecutionAnimData.generated.h"

USTRUCT(BlueprintType)
struct FExecutionInfo
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FGameplayTag Tag;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSoftObjectPtr<UAnimMontage> Animation;
};

/**
 * Data Asset for Execution Animations.
 */
UCLASS(BlueprintType)
class SLF_5_7_API UPDA_ExecutionAnimData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
    UPDA_ExecutionAnimData();

	/** Front Execution Info */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Execution")
	FExecutionInfo ExecuteFront;

	/** Back Execution Info */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Execution")
	FExecutionInfo ExecuteBack;

	/** Debug flag */
	UPROPERTY(EditAnywhere, Category = "Debug")
	bool DEBUG_DEFAULT_CHECK = true;
};
