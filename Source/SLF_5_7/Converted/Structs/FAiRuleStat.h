#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Enums/E_ValueType.h"
#include "FAiRuleStat.generated.h"

USTRUCT(BlueprintType)
struct SLF_5_7_API FAiRuleStat
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Boss")
    FGameplayTag StatTag;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Boss")
    float TargetValue = 0.0f;

    // Optional: Type of comparison or value type if complex logic is needed
    // UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Boss")
    // E_ValueType ValueType = E_ValueType::Current; 
};
