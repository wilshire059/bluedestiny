#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "Curves/CurveFloat.h"
#include "PDA_Buff.generated.h"

UCLASS(BlueprintType)
class SLF_5_7_API UPDA_Buff : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPDA_Buff();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buff")
	FGameplayTag BuffTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buff")
	TSoftObjectPtr<UTexture2D> BuffIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buff", meta = (AllowAbstract = "true"))
	TSoftClassPtr<AActor> BuffClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buff")
	float Duration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buff")
	TSoftObjectPtr<UCurveFloat> RankMultiplierCurve;
};
