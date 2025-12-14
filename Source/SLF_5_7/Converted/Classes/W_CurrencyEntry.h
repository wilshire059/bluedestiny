#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "W_CurrencyEntry.generated.h"

UCLASS()
class SLF_5_7_API UW_CurrencyEntry : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UImage> CurrencyIcon;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> CurrencyAmountText;

	UFUNCTION(BlueprintCallable, Category = "Currency")
	void SetupCurrencyEntry(UTexture2D* Icon, int64 Amount);

	UFUNCTION(BlueprintCallable, Category = "Currency")
	void UpdateAmount(int64 NewAmount);
};
