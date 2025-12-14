#pragma once

#include "CoreMinimal.h"
#include "W_UserWidget_Base.h"
#include "GameplayTagContainer.h"
#include "Components/VerticalBox.h"
#include "W_Equipment_Item_AttackPower.generated.h"

UCLASS()
class SLF_5_7_API UW_Equipment_Item_AttackPower : public UW_UserWidget_Base
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UVerticalBox> AttackPowerContainer;

	UFUNCTION(BlueprintCallable, Category = "Equipment")
	void SetupAttackPowerStats(const TMap<FGameplayTag, int32>& TargetAttackPowerStats,
		const TMap<FGameplayTag, int32>& CurrentAttackPowerStats, bool bCanCompare);

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Equipment")
	void OnSetupAttackPowerStats(const TMap<FGameplayTag, int32>& TargetStats,
		const TMap<FGameplayTag, int32>& CurrentStats, bool bCanCompare);
};
