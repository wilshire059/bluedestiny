#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "FStatBehavior.h"
#include "FStatInfo.generated.h"

USTRUCT(BlueprintType)
struct SLF_5_7_API FStatInfo
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    FGameplayTag Tag;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    float Value = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    float MaxValue = 100.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    FStatBehavior StatModifiers;

    // Backward compatibility alias
    FGameplayTag GetStatTag() const { return Tag; }
};
