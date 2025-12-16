#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimMontage.h"
#include "FAiAttackEntry.generated.h"

USTRUCT(BlueprintType)
struct FAiAttackEntry
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UAnimMontage> AttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double Weight = 1.0;
};
