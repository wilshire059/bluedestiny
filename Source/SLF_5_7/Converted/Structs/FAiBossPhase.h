#pragma once

#include "CoreMinimal.h"
#include "Structs/FAiRuleStat.h"
#include "DataAssets/PDA_AI_Ability.h"
#include "FAiBossPhase.generated.h"

class USoundBase;
class ULevelSequence;
class UAnimMontage;

USTRUCT(BlueprintType)
struct SLF_5_7_API FAiBossPhase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Boss|Abilities")
    TArray<TObjectPtr<UPDA_AI_Ability>> PhaseAbilities;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Boss|Requirements")
    FAiRuleStat RequiredStat;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Boss|Sequence")
    TSoftObjectPtr<ULevelSequence> PhaseStartSequence;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Boss|Montage")
    TSoftObjectPtr<UAnimMontage> PhaseStartMontage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Boss|Music")
    TSoftObjectPtr<USoundBase> PhaseMusic;
};
