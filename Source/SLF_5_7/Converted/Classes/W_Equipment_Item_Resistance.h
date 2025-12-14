#pragma once

#include "CoreMinimal.h"
#include "W_UserWidget_Base.h"
#include "GameplayTagContainer.h"
#include "Components/VerticalBox.h"
#include "W_Equipment_Item_Resistance.generated.h"

UCLASS()
class SLF_5_7_API UW_Equipment_Item_Resistance : public UW_UserWidget_Base
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UVerticalBox> ResistanceContainer;

	UFUNCTION(BlueprintCallable, Category = "Equipment")
	void SetupResistanceStats(const TMap<FGameplayTag, int32>& TargetResistanceStats,
		const TMap<FGameplayTag, int32>& CurrentResistanceStats, bool bCanCompare);

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Equipment")
	void OnSetupResistanceStats(const TMap<FGameplayTag, int32>& TargetStats,
		const TMap<FGameplayTag, int32>& CurrentStats, bool bCanCompare);
};
