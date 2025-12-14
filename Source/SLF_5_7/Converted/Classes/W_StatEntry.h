#pragma once

#include "CoreMinimal.h"
#include "W_UserWidget_Base.h"
#include "Classes/B_Stat.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "W_StatEntry.generated.h"

UCLASS()
class SLF_5_7_API UW_StatEntry : public UW_UserWidget_Base
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat", meta = (ExposeOnSpawn = "true"))
    UB_Stat* Stat;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat", meta = (ExposeOnSpawn = "true"))
    bool bShowAdjustButtons = true;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    TObjectPtr<UButton> ButtonIncrease;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    TObjectPtr<UButton> ButtonDecrease;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    TObjectPtr<UTextBlock> StatNameText;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    TObjectPtr<UTextBlock> StatValueText;

    UFUNCTION(BlueprintCallable, Category = "StatEntry")
    void UpdateUI(double NewValue, double MaxValue);

protected:
    virtual void NativeConstruct() override;

    UFUNCTION()
    void OnStatUpdated(double NewValue, double MaxValue, double Percent);

    UFUNCTION()
    void OnIncreaseClicked();

    UFUNCTION()
    void OnDecreaseClicked();
};
