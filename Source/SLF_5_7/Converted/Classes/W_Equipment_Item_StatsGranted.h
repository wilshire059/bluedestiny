#pragma once

#include "CoreMinimal.h"
#include "W_UserWidget_Base.h"
#include "GameplayTagContainer.h"
#include "Components/VerticalBox.h"
#include "W_Equipment_Item_StatsGranted.generated.h"

UCLASS()
class SLF_5_7_API UW_Equipment_Item_StatsGranted : public UW_UserWidget_Base
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UVerticalBox> StatsGrantedContainer;

	UFUNCTION(BlueprintCallable, Category = "Equipment")
	void SetupStatsGranted(const TMap<FGameplayTag, int32>& StatsGranted);

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Equipment")
	void OnSetupStatsGranted(const TMap<FGameplayTag, int32>& Stats);
};
