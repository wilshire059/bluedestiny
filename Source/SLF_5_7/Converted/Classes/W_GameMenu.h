#pragma once

#include "CoreMinimal.h"
#include "W_UserWidget_Base.h"
#include "W_GameMenu_Button.h"
#include "GameplayTagContainer.h"
#include "Components/SlateWrapperTypes.h"
#include "W_GameMenu.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameMenuWidgetRequest, FGameplayTag, Tag);

UCLASS()
class SLF_5_7_API UW_GameMenu : public UW_UserWidget_Base
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite, Category = "Menu")
    TArray<UW_GameMenu_Button*> MenuButtons;

    UPROPERTY(BlueprintAssignable, Category = "Menu")
    FOnGameMenuWidgetRequest OnGameMenuWidgetRequest;

    UFUNCTION(BlueprintCallable, Category = "Menu")
    void OnMenuButtonSelected(UW_GameMenu_Button* SelectedButton, bool bSelected);

    // virtual void NativeOnVisibilityChanged(ESlateVisibility InVisibility) override;
};
