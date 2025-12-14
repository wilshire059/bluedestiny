#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/VerticalBox.h"
#include "W_Browser_Categories.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBrowserCategorySelected, int32, CategoryIndex);

UCLASS()
class SLF_5_7_API UW_Browser_Categories : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UVerticalBox> CategoriesContainer;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnBrowserCategorySelected OnBrowserCategorySelected;

	UFUNCTION(BlueprintCallable, Category = "Browser")
	void SetupCategories(const TArray<FText>& Categories);

	UFUNCTION(BlueprintCallable, Category = "Browser")
	void SelectCategory(int32 CategoryIndex);

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Browser")
	void OnSetupCategories(const TArray<FText>& Categories);
};
