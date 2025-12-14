#pragma once

#include "CoreMinimal.h"
#include "B_StatusEffect.h"
#include "B_StatusEffect_Poison.generated.h"

UCLASS(Blueprintable, BlueprintType)
class SLF_5_7_API UB_StatusEffect_Poison : public UB_StatusEffect
{
	GENERATED_BODY()

public:
	UB_StatusEffect_Poison();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Poison")
	float PoisonDamagePerSecond;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Poison")
	float PoisonDuration;

	virtual void OnTriggered_Implementation() override;
	virtual void OnTick_Implementation(float DeltaTime) override;
};
