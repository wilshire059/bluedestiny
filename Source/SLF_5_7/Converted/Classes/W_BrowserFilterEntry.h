#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/CheckBox.h"
#include "W_BrowserFilterEntry.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnBrowserFilterChanged, int32, FilterIndex, bool, bEnabled);

UCLASS()
class SLF_5_7_API UW_BrowserFilterEntry : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UCheckBox> FilterCheckBox;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> FilterNameText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	int32 FilterIndex = 0;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnBrowserFilterChanged OnBrowserFilterChanged;

	UFUNCTION(BlueprintCallable, Category = "Browser")
	void SetupFilter(int32 InFilterIndex, FText FilterName, bool bInitialValue);

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void HandleFilterChanged(bool bIsChecked);
};
