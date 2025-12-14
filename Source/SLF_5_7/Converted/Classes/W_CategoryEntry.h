#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "W_CategoryEntry.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCategoryEntrySelected, int32, CategoryIndex);

UCLASS()
class SLF_5_7_API UW_CategoryEntry : public UUserWidget
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
	FText CategoryDisplayName;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnCategoryEntrySelected OnCategoryEntrySelected;

	UFUNCTION(BlueprintCallable, Category = "Category")
	void SetSelected(bool bSelected);

protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

	UFUNCTION()
	void HandleButtonClicked();
};
