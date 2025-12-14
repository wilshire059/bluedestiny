#pragma once

#include "CoreMinimal.h"
#include "W_UserWidget_Base.h"
#include "GameplayTagContainer.h"
#include "Components/VerticalBox.h"
#include "W_Equipment_Item_RequiredStats.generated.h"

UCLASS()
class SLF_5_7_API UW_Equipment_Item_RequiredStats : public UW_UserWidget_Base
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UVerticalBox> RequiredStatsContainer;

	UFUNCTION(BlueprintCallable, Category = "Equipment")
	void SetupRequiredStats(const TMap<FGameplayTag, int32>& RequiredStats,
		const TMap<FGameplayTag, int32>& CurrentStats);

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Equipment")
	void OnSetupRequiredStats(const TMap<FGameplayTag, int32>& Required,
		const TMap<FGameplayTag, int32>& Current);
};
