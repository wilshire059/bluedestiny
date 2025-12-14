#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DataAssets/PDA_Item.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "W_EquipmentSlot.generated.h"

class UPDA_Item;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOccupiedEquipmentSlot, UPDA_Item*, AssignedItem);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnClearEquipmentSlot);

UCLASS()
class SLF_5_7_API UW_EquipmentSlot : public UUserWidget
{
	GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
    UPDA_Item* AssignedItem;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
    bool bIsOccupied;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TSoftObjectPtr<UTexture2D> BackgroundIcon;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnOccupiedEquipmentSlot OnOccupiedEquipmentSlot;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnClearEquipmentSlot OnClearEquipmentSlot;

    // Components
    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
    UImage* ItemBackgroundIcon;

    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
    UImage* ItemIcon;

    // Functions
    UFUNCTION(BlueprintCallable, Category = "Equipment")
    void OccupyEquipmentSlot(UPDA_Item* Item);

    UFUNCTION(BlueprintCallable, Category = "Equipment")
    void ClearEquipmentSlot();

protected:
    virtual void NativePreConstruct() override;
};
