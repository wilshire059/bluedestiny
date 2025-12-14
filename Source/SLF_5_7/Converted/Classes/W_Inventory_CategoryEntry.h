#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Structs/FInventoryCategory.h"
#include "Components/Image.h"
#include "W_Inventory_CategoryEntry.generated.h"

// Forward Declaration
class UButton;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInventoryCategorySelected, UW_Inventory_CategoryEntry*, CategoryEntry);

UCLASS()
class SLF_5_7_API UW_Inventory_CategoryEntry : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Content")
	FInventoryCategory InventoryCategoryData;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnInventoryCategorySelected OnCategorySelected;

	UPROPERTY(BlueprintReadWrite, Category = "State")
	bool bIsSelected;

	// Components
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UImage* CategoryIconImage;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* Button;

	UFUNCTION(BlueprintCallable, Category = "UI")
	void SetInventoryCategorySelected(bool bSelected);

protected:
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void OnButtonClicked();

	UFUNCTION()
	void OnButtonHovered();

	UFUNCTION()
	void OnButtonUnhovered();
};
