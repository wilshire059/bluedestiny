#pragma once

#include "CoreMinimal.h"
#include "W_UserWidget_Base.h"
#include "Components/VerticalBox.h"
#include "W_StatBlock_LevelUp.generated.h"

UCLASS()
class SLF_5_7_API UW_StatBlock_LevelUp : public UW_UserWidget_Base
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UVerticalBox> StatBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	bool bShowUpgradeButtons = true;

protected:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable, Category = "LevelUp")
	void SetupStats();

	UFUNCTION(BlueprintImplementableEvent, Category = "LevelUp")
	void OnSetupStats();
};
