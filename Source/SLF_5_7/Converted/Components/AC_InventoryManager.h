#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "Structs/FInventoryItem.h"
#include "Structs/FSLFItemInfo.h"
#include "DataAssets/PDA_Item.h"
#include "Enums/E_InventorySlotType.h"
#include "AC_InventoryManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInventoryUpdated, const UPDA_Item*, Item);

UCLASS(ClassGroup=(Custom), Blueprintable, meta=(BlueprintSpawnableComponent))
class SLF_5_7_API UAC_InventoryManager : public UActorComponent
{
    GENERATED_BODY()

public:    
    UAC_InventoryManager();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
    TArray<FInventoryItem> Inventory;

    UPROPERTY(BlueprintAssignable, Category = "Inventory")
    FOnInventoryUpdated OnInventoryUpdated;

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    int32 GetAmountOfItem(UPDA_Item* Item) const;
    
    UFUNCTION(BlueprintCallable, Category = "Inventory")
    int32 GetAmountOfItemByTag(FGameplayTag ItemTag) const;

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    void RemoveItem(UPDA_Item* Item, int32 Count);

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    void AddItem(UPDA_Item* Item, int32 Count);

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    void GetSlotWithItemTag(FGameplayTag ItemTag, E_InventorySlotType SlotType); 

    // Currency
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
    int32 Currency = 0;

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    void AdjustCurrency(int32 Delta);

    // Helper to find item index
    int32 FindItemIndex(UPDA_Item* Item) const;
};
