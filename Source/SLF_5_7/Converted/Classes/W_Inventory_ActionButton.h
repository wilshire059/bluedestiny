#pragma once

#include "CoreMinimal.h"
#include "W_UserWidget_Base.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "W_Inventory_ActionButton.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActionButtonClicked, int32, ActionIndex);

UCLASS()
class SLF_5_7_API UW_Inventory_ActionButton : public UW_UserWidget_Base
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> ActionButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> ActionText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	int32 ActionIndex = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	FText ActionName;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnActionButtonClicked OnActionButtonClicked;

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void HandleButtonClicked();
};
