#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "B_StatusEffectBuildup.generated.h"

class UPDA_StatusEffect;

UCLASS(Blueprintable, BlueprintType)
class SLF_5_7_API AB_StatusEffectBuildup : public AActor
{
	GENERATED_BODY()

public:
	AB_StatusEffectBuildup();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status Effect Buildup")
	TObjectPtr<UPDA_StatusEffect> StatusEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status Effect Buildup")
	float BuildupAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status Effect Buildup")
	int32 Rank;

	UFUNCTION(BlueprintCallable, Category = "Status Effect Buildup")
	void ApplyToActor(AActor* TargetActor);

protected:
	virtual void BeginPlay() override;
};
