#pragma once

#include "CoreMinimal.h"
#include "W_UserWidget_Base.h"
#include "W_StatBlock.h"
#include "Components/AC_StatManager.h"
#include "W_Status.generated.h"

UCLASS()
class SLF_5_7_API UW_Status : public UW_UserWidget_Base
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
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
