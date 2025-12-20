#pragma once

#include "CoreMinimal.h"
#include "W_UserWidget_Base.h"
#include "Components/Border.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "W_Inventory_ActionButton.generated.h"

// Forward declarations
class UW_Inventory_ActionButton;

// Delegates
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnActionButtonPressed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActionButtonSelected, UW_Inventory_ActionButton*, Button);

/**
 * Inventory Action Button Widget
 * Displays individual action buttons in the inventory system with selection states
 */
UCLASS()
class SLF_5_7_API UW_Inventory_ActionButton : public UW_UserWidget_Base
{
	GENERATED_BODY()

public:
	// Constructor
	UW_Inventory_ActionButton(const FObjectInitializer& ObjectInitializer);

	// Widget Components
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UBorder> Btn;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> Txt;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> UseButton;

	// Properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action Button")
	FText ActionText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action Button")
	FLinearColor Color;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action Button")
	FLinearColor SelectedColor;

	UPROPERTY(BlueprintReadWrite, Category = "Action Button")
	bool bSelected;

	// Delegates
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnActionButtonPressed OnActionButtonPressed;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnActionButtonSelected OnActionButtonSelected;

	// Functions
	UFUNCTION(BlueprintCallable, Category = "Action Button")
	void SetActionButtonSelected(bool bNewSelected);

	UFUNCTION(BlueprintImplementableEvent, Category = "Action Button")
	void ActionPressed();

protected:
	// UUserWidget interface
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

private:
	// Button event handlers
	UFUNCTION()
	void OnUseButtonPressed();

	UFUNCTION()
	void OnUseButtonHovered();
};
