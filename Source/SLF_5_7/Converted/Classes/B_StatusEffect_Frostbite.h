#pragma once

#include "CoreMinimal.h"
#include "B_StatusEffect.h"
#include "B_StatusEffect_Frostbite.generated.h"

UCLASS(Blueprintable, BlueprintType)
class SLF_5_7_API UB_StatusEffect_Frostbite : public UB_StatusEffect
{
	GENERATED_BODY()

public:
	UB_StatusEffect_Frostbite();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Frostbite")
	float DamageNegationReduction;

	virtual void OnTriggered_Implementation() override;
	virtual void OnRemoved_Implementation() override;
};
