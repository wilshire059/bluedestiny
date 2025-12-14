#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "Curves/CurveFloat.h"
#include "PDA_StatusEffect.generated.h"

class UPDA_Item;

UCLASS(BlueprintType)
class SLF_5_7_API UPDA_StatusEffect : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPDA_StatusEffect();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status Effect")
	FGameplayTag Tag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status Effect", meta = (AllowAbstract = "true"))
	TSoftClassPtr<AActor> Effect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status Effect")
	TSoftObjectPtr<UTexture2D> Icon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status Effect")
	FLinearColor BarFillColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status Effect")
	FText TriggeredText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status Effect")
	FGameplayTag ResistiveStat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status Effect")
	TObjectPtr<UCurveFloat> ResistiveStatCurve;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status Effect")
	TArray<TObjectPtr<UPDA_Item>> MitigatedBy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status Effect")
	TArray<TObjectPtr<UPDA_Item>> CuredBy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status Effect")
	double BaseBuildupRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status Effect")
	double BaseDecayRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status Effect")
	double DecayDelay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status Effect")
	bool bCanRetrigger;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status Effect")
	TMap<int32, int32> RankInfo;
};
