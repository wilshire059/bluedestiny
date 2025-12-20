#pragma once

#include "CoreMinimal.h"
#include "W_UserWidget_Base.h"
#include "W_StatBlock.h"
#include "Components/AC_StatManager.h"
#include "Components/Image.h"
#include "Components/HorizontalBox.h"
#include "Components/BackgroundBlur.h"
#include "W_Status.generated.h"

class UW_Status_StatBlock;
class UW_Status_LevelCurrencyBlock;

UCLASS()
class SLF_5_7_API UW_Status : public UW_UserWidget_Base
{
    GENERATED_BODY()

public:
    // ==================== Input Icons ====================
    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    TObjectPtr<UImage> BackInputIcon;

    // ==================== Layout Containers ====================
    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    TObjectPtr<UHorizontalBox> ButtonsBox;

    // ==================== Background/Blur ====================
    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    TObjectPtr<UBackgroundBlur> MainBlur;

    // ==================== Decorative Images ====================
    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    TObjectPtr<UImage> Image;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    TObjectPtr<UImage> Image_1;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    TObjectPtr<UImage> Image_4;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    TObjectPtr<UImage> Image_5;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    TObjectPtr<UImage> Image_134;

    // ==================== Stat Block Widgets ====================
    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    TObjectPtr<UW_Status_StatBlock> W_StatBlock_Status;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    TObjectPtr<UW_Status_StatBlock> W_StatBlock_Status_1;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    TObjectPtr<UW_Status_StatBlock> W_StatBlock_Status_3;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    TObjectPtr<UW_Status_StatBlock> W_StatBlock_Status_5;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    TObjectPtr<UW_Status_StatBlock> W_StatBlock_Status_7;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    TObjectPtr<UW_Status_StatBlock> W_StatBlock_Status_8;

    // ==================== Level/Currency Block ====================
    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    TObjectPtr<UW_Status_LevelCurrencyBlock> W_Status_LevelCurrencyBlock;

    // ==================== Legacy/Compatibility ====================
    UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
    TObjectPtr<UW_StatBlock> StatBlock;

    UPROPERTY(Transient, meta = (BindWidgetAnim))
    TObjectPtr<UWidgetAnimation> Fade;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
    int32 CurrentPlayerLevel;

protected:
    virtual void NativeConstruct() override;

    UFUNCTION()
    void OnLevelUpdated(int32 Level);

    // NOTE: OnVisibilityChanged is not easily overridable in UUserWidget.
    // If needed, hook into NativeOnVisibilityChanged instead.
};
