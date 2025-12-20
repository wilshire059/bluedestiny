#pragma once

#include "CoreMinimal.h"
#include "W_UserWidget_Base.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Enums/E_ItemCategory.h"
#include "Structs/FInventoryCategory.h"
#include "W_Inventory_CategoryEntry.generated.h"

// Forward declarations
class UW_Inventory_CategoryEntry;

// Delegates
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCategorySelected, UW_Inventory_CategoryEntry*, CategoryEntry, E_ItemCategory, SelectedCategory);

/**
 * Inventory Category Entry Widget
 * Represents a single category button in the inventory menu
 */
UCLASS()
class SLF_5_7_API UW_Inventory_CategoryEntry : public UW_UserWidget_Base
{
	GENERATED_BODY()

public:
	// Constructor
	UW_Inventory_CategoryEntry(const FObjectInitializer& ObjectInitializer);

	// Widget Components
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> Button;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UImage> CategoryIcon;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UImage> SelectedGlow;

	// Properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Category Entry")
	bool bAllCategoriesButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Category Entry")
	FInventoryCategory InventoryCategoryData;

	UPROPERTY(BlueprintReadWrite, Category = "Category Entry")
	bool bSelected;

	// Delegates
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnCategorySelected OnSelected;

	// Functions
	UFUNCTION(BlueprintCallable, Category = "Category Entry")
	void SetInventoryCategorySelected(bool bNewSelected, const FSlateColor& HoveredColor, const FSlateColor& UnhoveredColor);

protected:
	// UUserWidget interface
	virtual void NativeConstruct() override;
	virtual void NativePreConstruct() override;

private:
	// Button event handlers
	UFUNCTION()
	void OnButtonClicked();

	UFUNCTION()
	void OnButtonHovered();

	UFUNCTION()
	void OnButtonUnhovered();

	// Helper colors for hover/unhover states
	FSlateColor HoverTintColor;
	FSlateColor UnhoverTintColor;
};
