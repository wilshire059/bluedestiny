#pragma once

#include "CoreMinimal.h"
#include "W_UserWidget_Base.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "GameplayTagContainer.h"
#include "W_GameMenu_Button.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMenuButtonSelected, UW_GameMenu_Button*, Button, bool, bSelected);

UCLASS()
class SLF_5_7_API UW_GameMenu_Button : public UW_UserWidget_Base
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (ExposeOnSpawn = "true"))
    FGameplayTag WidgetTag;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    TObjectPtr<UButton> Button;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    TObjectPtr<UTextBlock> Label;

    UPROPERTY(BlueprintCallable, BlueprintAssignable)
    FOnMenuButtonSelected OnSelected;

    UFUNCTION(BlueprintCallable)
    void SetGameMenuButtonSelected(bool bSelected);

protected:
    virtual void NativeConstruct() override;

    UFUNCTION()
    void OnButtonClicked();
};
