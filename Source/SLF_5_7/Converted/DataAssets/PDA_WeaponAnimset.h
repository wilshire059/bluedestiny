#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PDA_WeaponAnimset.generated.h"

UCLASS(BlueprintType)
class SLF_5_7_API UPDA_WeaponAnimset : public UPrimaryDataAsset
{
    GENERATED_BODY()
public:
    // Stub for now, likely contains Montages
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
    UAnimMontage* DefaultAttackMontage;
};
