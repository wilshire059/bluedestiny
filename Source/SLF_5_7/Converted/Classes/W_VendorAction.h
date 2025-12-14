#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "W_VendorAction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnVendorActionClicked, int32, ActionType);

UCLASS()
class SLF_5_7_API UW_VendorAction : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> ActionButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> ActionText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> PriceText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	int32 ActionType = 0; // 0 = Buy, 1 = Sell

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnVendorActionClicked OnVendorActionClicked;

	UFUNCTION(BlueprintCallable, Category = "Vendor")
	void SetupAction(int32 InActionType, FText ActionLabel, int64 Price);

	UFUNCTION(BlueprintCallable, Category = "Vendor")
	void SetCanAfford(bool bCanAfford);

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void HandleActionClicked();
};
