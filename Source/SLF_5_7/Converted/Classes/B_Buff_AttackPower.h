#pragma once

#include "CoreMinimal.h"
#include "B_Buff.h"
#include "B_Buff_AttackPower.generated.h"

UCLASS(Blueprintable, BlueprintType)
class SLF_5_7_API UB_Buff_AttackPower : public UB_Buff
{
	GENERATED_BODY()

public:
	UB_Buff_AttackPower();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack Power Buff")
	FGameplayTag AttackPowerTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack Power Buff")
	float AttackPowerBonus;

	virtual void OnGranted_Implementation() override;
	virtual void OnRemoved_Implementation() override;
};
