#pragma once

#include "CoreMinimal.h"
#include "W_UserWidget_Base.h"
#include "W_InventoryActionAmount.h"
#include "Components/Image.h"
#include "W_InventoryAction.generated.h"

UCLASS()
class SLF_5_7_API UW_InventoryAction : public UW_UserWidget_Base
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    TObjectPtr<UW_InventoryActionAmount> AmountActionPanel;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    TObjectPtr<UImage> OkInputIcon;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    TObjectPtr<UImage> BackInputIcon;

    UFUNCTION(BlueprintCallable)
    void UpdateOkInputIcons(TSoftObjectPtr<UTexture2D> OkInputTexture);

    UFUNCTION(BlueprintCallable)
    void UpdateBackInputIcons(TSoftObjectPtr<UTexture2D> BackInputTexture);
};
