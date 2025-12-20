#pragma once

#include "CoreMinimal.h"
#include "FAiSenseTargetInfo.generated.h"

USTRUCT(BlueprintType)
struct SLF_5_7_API FAiSenseTargetInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Sense")
	TObjectPtr<AActor> SensedTarget;
};
