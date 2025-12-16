#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "FEquipmentItemsSaveInfo.generated.h"

class UPDA_Item;

USTRUCT(BlueprintType)
struct SLF_5_7_API FEquipmentItemsSaveInfo
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save")
    FGameplayTag SlotTag;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save")
    TSoftObjectPtr<UPDA_Item> EquippedItem;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save")
    int32 SlotIndex = 0;

    FEquipmentItemsSaveInfo()
        : SlotIndex(0)
    {}
};
