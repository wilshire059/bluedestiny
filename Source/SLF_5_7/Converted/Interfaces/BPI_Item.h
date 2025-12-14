#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BPI_Item.generated.h"

UINTERFACE(MinimalAPI)
class UBPI_Item : public UInterface
{
    GENERATED_BODY()
};

class SLF_5_7_API IBPI_Item
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Item")
    void OnUse();

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Item")
    void OnWeaponEquip(bool bRightHand);

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Item")
    void OnWeaponUnequip();
};
