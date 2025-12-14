#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Structs/FSLFItemInfo.h"
#include "PDA_Item.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCraftingUnlocked);

UCLASS(BlueprintType)
class SLF_5_7_API UPDA_Item : public UPrimaryDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    FSLFItemInfo ItemInformation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting")
    bool bCraftingUnlocked = false;

    UPROPERTY(BlueprintAssignable, Category = "Crafting")
    FOnCraftingUnlocked OnCraftingUnlocked;

    UFUNCTION(BlueprintCallable, Category = "Crafting")
    void UnlockCrafting();

    UFUNCTION(BlueprintPure, Category = "Crafting")
    TMap<FGameplayTag, int32> GetRequiredCraftingItems() const;
};
