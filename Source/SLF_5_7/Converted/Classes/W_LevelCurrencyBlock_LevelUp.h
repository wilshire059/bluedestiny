#pragma once

#include "CoreMinimal.h"
#include "W_UserWidget_Base.h"
#include "Components/TextBlock.h"
#include "W_LevelCurrencyBlock_LevelUp.generated.h"

UCLASS()
class SLF_5_7_API UW_LevelCurrencyBlock_LevelUp : public UW_UserWidget_Base
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> CurrentLevelText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> NewLevelText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> CurrentCurrencyText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> RequiredCurrencyText;

	UFUNCTION(BlueprintCallable, Category = "LevelUp")
	void UpdateDisplay(int32 CurrentLevel, int32 NewLevel, int64 CurrentCurrency, int64 RequiredCurrency);

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void RefreshDisplay();
};
