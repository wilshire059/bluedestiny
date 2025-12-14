#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DataAssets/PDA_Item.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "W_InventorySlot.generated.h"

class UPDA_Item;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnOccupiedSlot, UPDA_Item*, AssignedItem, int32, Count);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnClearSlot);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangeAmount, int32, NewCount);

UCLASS()
class SLF_5_7_API UW_InventorySlot : public UUserWidget
{
	GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
    UPDA_Item* AssignedItem;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
    bool bIsOccupied;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
    int32 ItemAmountValue;

    // Events
    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnOccupiedSlot OnOccupiedSlot;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnClearSlot OnClearSlot;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnChangeAmount OnChangeAmount;

    // Components
    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
    UImage* ItemIcon;

    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
    UTextBlock* ItemAmount;

    // Functions
    UFUNCTION(BlueprintCallable, Category = "Inventory")
    void OccupySlot(UPDA_Item* Item, int32 Count);

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    void ClearSlot();

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    void ChangeAmount(int32 NewCount);
};
