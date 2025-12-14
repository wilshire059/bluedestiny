#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Enums/E_SettingCategory.h"
#include "W_Settings_CategoryEntry.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSettingsCategorySelected, int32, CategoryIndex);

UCLASS()
class SLF_5_7_API UW_Settings_CategoryEntry : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> CategoryButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> CategoryNameText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	int32 CategoryIndex = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	E_SettingCategory Category;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	FText CategoryDisplayName;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnSettingsCategorySelected OnSettingsCategorySelected;

	UFUNCTION(BlueprintCallable, Category = "Settings")
	void SetSelected(bool bSelected);

protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

	UFUNCTION()
	void HandleButtonClicked();
};
