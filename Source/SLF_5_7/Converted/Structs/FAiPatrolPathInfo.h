#pragma once

#include "CoreMinimal.h"
#include "Classes/B_PatrolPath.h"
#include "FAiPatrolPathInfo.generated.h"

USTRUCT(BlueprintType)
struct SLF_5_7_API FAiPatrolPathInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	class AB_PatrolPath* PatrolPath = nullptr;
};
