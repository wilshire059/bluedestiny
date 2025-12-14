#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimMontage.h"
#include "FExecutionAnimInfo.generated.h"

USTRUCT(BlueprintType)
struct FExecutionAnimInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAnimMontage> Executor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAnimMontage> Receiver;
};
