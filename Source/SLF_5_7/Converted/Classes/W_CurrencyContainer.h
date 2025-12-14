#pragma once

#include "CoreMinimal.h"
#include "W_UserWidget_Base.h"
#include "Components/HorizontalBox.h"
#include "W_CurrencyContainer.generated.h"

UCLASS()
class SLF_5_7_API UW_CurrencyContainer : public UW_UserWidget_Base
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UHorizontalBox> CurrencyEntriesContainer;

	UFUNCTION(BlueprintCallable, Category = "Currency")
	void RefreshCurrencies();

protected:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintImplementableEvent, Category = "Currency")
	void OnRefreshCurrencies();
};
