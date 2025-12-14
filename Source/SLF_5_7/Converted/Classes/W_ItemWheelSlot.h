#pragma once

#include "CoreMinimal.h"
#include "W_UserWidget_Base.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Structs/FInventoryItem.h"
#include "W_ItemWheelSlot.generated.h"

UCLASS()
class SLF_5_7_API UW_ItemWheelSlot : public UW_UserWidget_Base
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UImage> ItemIcon;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> QuantityText;

	UPROPERTY(BlueprintReadWrite, Category = "State")
	FInventoryItem CurrentItem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	int32 SlotIndex = 0;

	UFUNCTION(BlueprintCallable, Category = "ItemWheel")
	void SetupSlot(const FInventoryItem& Item);

	UFUNCTION(BlueprintCallable, Category = "ItemWheel")
	void UpdateQuantity(int32 Quantity);

	UFUNCTION(BlueprintCallable, Category = "ItemWheel")
	void ClearSlot();
};
