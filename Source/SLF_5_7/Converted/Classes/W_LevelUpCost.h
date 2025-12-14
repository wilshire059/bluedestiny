#pragma once

#include "CoreMinimal.h"
#include "W_UserWidget_Base.h"
#include "Components/TextBlock.h"
#include "W_LevelUpCost.generated.h"

UCLASS()
class SLF_5_7_API UW_LevelUpCost : public UW_UserWidget_Base
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> CostText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> CurrentCurrencyText;

	UFUNCTION(BlueprintCallable, Category = "LevelUp")
	void UpdateCostDisplay(int64 Cost, int64 CurrentCurrency);
};
