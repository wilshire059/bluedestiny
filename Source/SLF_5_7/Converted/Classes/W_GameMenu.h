#pragma once

#include "CoreMinimal.h"
#include "W_UserWidget_Base.h"
#include "W_GameMenu_Button.h"
#include "GameplayTagContainer.h"
#include "Components/SlateWrapperTypes.h"
#include "Components/Image.h"
#include "Components/VerticalBox.h"
#include "W_GameMenu.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameMenuWidgetRequest, FGameplayTag, Tag);

UCLASS()
class SLF_5_7_API UW_GameMenu : public UW_UserWidget_Base
{
    GENERATED_BODY()

public:
    // ==================== Input Icons ====================
    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    TObjectPtr<UImage> BackIcon;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    TObjectPtr<UImage> SelectIcon;

    // ==================== Layout Containers ====================
    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    TObjectPtr<UVerticalBox> GameMenuButtonsBox;

    // ==================== Menu Button Widgets ====================
    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    TObjectPtr<UW_GameMenu_Button> W_GMB_Crafting;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    TObjectPtr<UW_GameMenu_Button> W_GMB_Equipment;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    TObjectPtr<UW_GameMenu_Button> W_GMB_Inventory;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    TObjectPtr<UW_GameMenu_Button> W_GMB_Status;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    TObjectPtr<UW_GameMenu_Button> W_GMB_System;

    // ==================== State ====================
    UPROPERTY(BlueprintReadWrite, Category = "Menu")
    TArray<UW_GameMenu_Button*> MenuButtons;

    UPROPERTY(BlueprintAssignable, Category = "Menu")
    FOnGameMenuWidgetRequest OnGameMenuWidgetRequest;

    UFUNCTION(BlueprintCallable, Category = "Menu")
    void OnMenuButtonSelected(UW_GameMenu_Button* SelectedButton, bool bSelected);

    // virtual void NativeOnVisibilityChanged(ESlateVisibility InVisibility) override;
};
