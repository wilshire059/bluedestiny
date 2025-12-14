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

    virtual void OnVisibilityChanged_Implementation(ESlateVisibility InVisibility); // Override if available (Wait, Widget doesn't have virtual impl easily, use event)
    
    // UUserWidget doesn't have virtual OnVisibilityChanged exposed to BP in the same way.
    // We can hook into OnNativeVisibilityChanged or just override NativeOnVisibilityChanged if UE 5.
    // virtual void NativeOnVisibilityChanged(ESlateVisibility InVisibility) override;
};
