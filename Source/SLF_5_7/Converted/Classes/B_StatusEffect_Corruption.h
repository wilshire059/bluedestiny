#pragma once

#include "CoreMinimal.h"
#include "B_StatusEffect.h"
#include "B_StatusEffect_Corruption.generated.h"

UCLASS(Blueprintable, BlueprintType)
class SLF_5_7_API UB_StatusEffect_Corruption : public UB_StatusEffect
{
	GENERATED_BODY()

public:
	UB_StatusEffect_Corruption();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Corruption")
	float FPDrainPerSecond;

	virtual void OnTriggered_Implementation() override;
	virtual void OnTick_Implementation(float DeltaTime) override;
};
