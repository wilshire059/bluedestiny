#pragma once

#include "CoreMinimal.h"
#include "Classes/W_Navigable.h"
#include "W_Equipment.generated.h"

class UW_EquipmentSlot;

UCLASS()
class SLF_5_7_API UW_Equipment : public UW_Navigable
{
	GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
    int32 EquipmentSlotNavigationIndex;

    UPROPERTY(BlueprintReadWrite, Category = "Equipment")
    TArray<UW_EquipmentSlot*> EquipmentSlots;

    UFUNCTION(BlueprintCallable, Category = "Equipment")
    void NavigateSlots(bool bNext);
};
