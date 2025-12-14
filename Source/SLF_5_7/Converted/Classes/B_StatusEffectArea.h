#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "B_StatusEffectArea.generated.h"

class UPDA_StatusEffect;

UCLASS(Blueprintable, BlueprintType)
class SLF_5_7_API AB_StatusEffectArea : public AActor
{
	GENERATED_BODY()

public:
	AB_StatusEffectArea();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status Effect Area")
	TObjectPtr<UPDA_StatusEffect> StatusEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status Effect Area")
	float Radius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status Effect Area")
	float BuildupPerSecond;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status Effect Area")
	int32 Rank;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
