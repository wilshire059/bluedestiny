#pragma once

#include "CoreMinimal.h"
#include "Structs/FAiRuleStat.h"
#include "DataAssets/PDA_AI_Ability.h"
#include "FAiBossPhase.generated.h"

class USoundBase;

USTRUCT(BlueprintType)
struct SLF_5_7_API FAiBossPhase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Boss")
    TArray<UPDA_AI_Ability*> Abilities;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Boss")
    FAiRuleStat RequiredStat;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Boss")
    TSoftObjectPtr<USoundBase> PhaseMusic;
};
