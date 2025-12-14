#pragma once

#include "CoreMinimal.h"
#include "W_UserWidget_Base.h"
#include "Components/TextBlock.h"
#include "W_Status_LevelCurrencyBlock.generated.h"

UCLASS()
class SLF_5_7_API UW_Status_LevelCurrencyBlock : public UW_UserWidget_Base
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> LevelText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> CurrencyText;

	UFUNCTION(BlueprintCallable, Category = "Status")
	void UpdateLevelDisplay(int32 Level);

	UFUNCTION(BlueprintCallable, Category = "Status")
	void UpdateCurrencyDisplay(int64 Currency);

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void RefreshDisplay();
};
