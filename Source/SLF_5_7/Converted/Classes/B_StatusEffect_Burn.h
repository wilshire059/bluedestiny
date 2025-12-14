#pragma once

#include "CoreMinimal.h"
#include "B_StatusEffect.h"
#include "B_StatusEffect_Burn.generated.h"

UCLASS(Blueprintable, BlueprintType)
class SLF_5_7_API UB_StatusEffect_Burn : public UB_StatusEffect
{
	GENERATED_BODY()

public:
	UB_StatusEffect_Burn();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Burn")
	float BurnDamagePerSecond;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Burn")
	float BurnDuration;

	virtual void OnTriggered_Implementation() override;
	virtual void OnTick_Implementation(float DeltaTime) override;
};
