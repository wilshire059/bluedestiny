#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "W_Browser_CategoryEntry.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBrowserCategoryEntrySelected, int32, CategoryIndex);

UCLASS()
class SLF_5_7_API UW_Browser_CategoryEntry : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> CategoryButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> CategoryNameText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	int32 CategoryIndex = 0;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnBrowserCategoryEntrySelected OnBrowserCategoryEntrySelected;

	UFUNCTION(BlueprintCallable, Category = "Browser")
	void SetupEntry(int32 InCategoryIndex, FText InCategoryDisplayName);

	UFUNCTION(BlueprintCallable, Category = "Browser")
	void SetSelected(bool bSelected);

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void HandleCategoryClicked();
};
