#pragma once

#include "CoreMinimal.h"
#include "Classes/W_Navigable.h"
#include "W_Inventory.generated.h"

class UW_Inventory_CategoryEntry;

UCLASS()
class SLF_5_7_API UW_Inventory : public UW_Navigable
{
	GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
    int32 CategoryNavigationIndex;

    UPROPERTY(BlueprintReadWrite, Category = "Inventory")
    TArray<UW_Inventory_CategoryEntry*> CategoryEntries;

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    void GridUp();
    
    UFUNCTION(BlueprintCallable, Category = "Inventory")
    void GridDown();
    
    UFUNCTION(BlueprintCallable, Category = "Inventory")
    void GridLeft();
    
    UFUNCTION(BlueprintCallable, Category = "Inventory")
    void GridRight();

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    void NavigateCategories(bool bNext);
};
