#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Structs/FInventoryItem.h"
#include "W_VendorSlot.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnVendorSlotSelected, int32, SlotIndex);

UCLASS()
class SLF_5_7_API UW_VendorSlot : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> SlotButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UImage> ItemIcon;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> ItemNameText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> PriceText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	TObjectPtr<UTextBlock> QuantityText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	int32 SlotIndex = 0;

	UPROPERTY(BlueprintReadWrite, Category = "State")
	FInventoryItem ItemData;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnVendorSlotSelected OnVendorSlotSelected;

	UFUNCTION(BlueprintCallable, Category = "Vendor")
	void SetupSlot(int32 InSlotIndex, const FInventoryItem& Item, int64 Price);

	UFUNCTION(BlueprintCallable, Category = "Vendor")
	void SetSelected(bool bSelected);

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void HandleSlotClicked();
};
