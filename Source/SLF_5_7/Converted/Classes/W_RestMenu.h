#pragma once

#include "CoreMinimal.h"
#include "W_UserWidget_Base.h"
#include "Components/VerticalBox.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "W_RestMenu.generated.h"

class UW_RestMenu_Button;
class UW_LevelUp;
class UW_TimePass;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRestMenuAction, int32, ActionIndex);

UCLASS()
class SLF_5_7_API UW_RestMenu : public UW_UserWidget_Base
{
	GENERATED_BODY()

public:
	// ==================== Input Icons ====================
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UImage> BackInputIcon;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UImage> OkInputIcon;

	// ==================== Buttons ====================
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> BackButton;

	// ==================== Layout Containers ====================
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UVerticalBox> MainButtonsBox;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UVerticalBox> TimeEntriesBox;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	TObjectPtr<UVerticalBox> ButtonContainer;

	// ==================== Widget Switcher ====================
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UWidgetSwitcher> Switcher;

	// ==================== Images ====================
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UImage> InventoryImage;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UImage> InventoryImageBorder;

	// ==================== Text Widgets ====================
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> RestingLocationNameText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> TimeOfDayText;

	// ==================== Menu Button Widgets ====================
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UW_RestMenu_Button> W_RMB_Leave;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UW_RestMenu_Button> W_RMB_Levelup;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UW_RestMenu_Button> W_RMB_Rest;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UW_RestMenu_Button> W_RMB_SortChest;

	// ==================== Sub-Widgets ====================
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UW_LevelUp> W_LevelUp;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UW_TimePass> W_TimePass;

	// ==================== State ====================
	UPROPERTY(BlueprintReadWrite, Category = "Menu")
	TArray<UW_RestMenu_Button*> MenuButtons;

	// ==================== Events ====================
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnRestMenuAction OnRestMenuAction;

	// ==================== Functions ====================
	UFUNCTION(BlueprintCallable, Category = "RestMenu")
	void OnButtonClicked(int32 ButtonIndex);

	UFUNCTION(BlueprintCallable, Category = "RestMenu")
	void LevelUp();

	UFUNCTION(BlueprintCallable, Category = "RestMenu")
	void PassTime();

	UFUNCTION(BlueprintCallable, Category = "RestMenu")
	void SortChest();

	UFUNCTION(BlueprintCallable, Category = "RestMenu")
	void LeaveRestPoint();
};
