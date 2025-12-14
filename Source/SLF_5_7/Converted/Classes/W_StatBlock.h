#pragma once

#include "CoreMinimal.h"
#include "W_UserWidget_Base.h"
#include "Components/VerticalBox.h"
#include "W_StatBlock.generated.h"

UCLASS()
class SLF_5_7_API UW_StatBlock : public UW_UserWidget_Base
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (ExposeOnSpawn = "true"))
    bool bShowUpgradeButtons = false;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    TObjectPtr<UVerticalBox> StatBox;

protected:
    virtual void NativePreConstruct() override;
    virtual void NativeConstruct() override;

    UFUNCTION()
    void SetupCurrentStats();

    UFUNCTION()
    void OnStatsInitialized();
};
