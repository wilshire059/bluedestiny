#pragma once

#include "CoreMinimal.h"
#include "B_StatusEffect.h"
#include "B_StatusEffect_Bleed.generated.h"

UCLASS(Blueprintable, BlueprintType)
class SLF_5_7_API UB_StatusEffect_Bleed : public UB_StatusEffect
{
	GENERATED_BODY()

public:
	UB_StatusEffect_Bleed();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bleed")
	float BleedDamagePercent;

	virtual void OnTriggered_Implementation() override;
};
