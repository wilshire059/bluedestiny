#pragma once

#include "CoreMinimal.h"
#include "W_UserWidget_Base.h"
#include "Components/WidgetSwitcher.h"
#include "Components/HorizontalBox.h"
#include "W_Settings.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSettingsSaved);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSettingsCancelled);

UCLASS()
class SLF_5_7_API UW_Settings : public UW_UserWidget_Base
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UWidgetSwitcher> CategorySwitcher;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UHorizontalBox> CategoryTabsContainer;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnSettingsSaved OnSettingsSaved;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnSettingsCancelled OnSettingsCancelled;

	UFUNCTION(BlueprintCallable, Category = "Settings")
	void SwitchCategory(int32 CategoryIndex);

	UFUNCTION(BlueprintCallable, Category = "Settings")
	void ApplySettings();

	UFUNCTION(BlueprintCallable, Category = "Settings")
	void RevertSettings();

	UFUNCTION(BlueprintCallable, Category = "Settings")
	void CloseSettings();

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadWrite, Category = "State")
	int32 CurrentCategoryIndex = 0;
};
