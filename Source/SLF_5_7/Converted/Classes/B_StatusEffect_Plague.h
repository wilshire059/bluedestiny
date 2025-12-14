#pragma once

#include "CoreMinimal.h"
#include "B_StatusEffect.h"
#include "B_StatusEffect_Plague.generated.h"

UCLASS(Blueprintable, BlueprintType)
class SLF_5_7_API UB_StatusEffect_Plague : public UB_StatusEffect
{
	GENERATED_BODY()

public:
	UB_StatusEffect_Plague();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Plague")
	float PlagueDamagePercent;

	virtual void OnTriggered_Implementation() override;
};
