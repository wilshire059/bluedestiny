#pragma once

#include "CoreMinimal.h"
#include "W_UserWidget_Base.h"
#include "GameplayTagContainer.h"
#include "Components/VerticalBox.h"
#include "W_Equipment_Item_DamageNegation.generated.h"

UCLASS()
class SLF_5_7_API UW_Equipment_Item_DamageNegation : public UW_UserWidget_Base
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UVerticalBox> DamageNegationContainer;

	UFUNCTION(BlueprintCallable, Category = "Equipment")
	void SetupDamageNegationStats(const TMap<FGameplayTag, int32>& TargetDamageNegationStats,
		const TMap<FGameplayTag, int32>& CurrentDamageNegationStats, bool bCanCompare);

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Equipment")
	void OnSetupDamageNegationStats(const TMap<FGameplayTag, int32>& TargetStats,
		const TMap<FGameplayTag, int32>& CurrentStats, bool bCanCompare);
};
