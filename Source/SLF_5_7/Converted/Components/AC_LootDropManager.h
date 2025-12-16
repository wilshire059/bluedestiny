#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Structs/FLootItem.h"
#include "Structs/FWeightedLoot.h"
#include "Engine/DataTable.h"
#include "AC_LootDropManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemReadyForSpawn, FLootItem, Item);

UCLASS( ClassGroup=(Custom), Blueprintable, meta=(BlueprintSpawnableComponent) )
class SLF_5_7_API UAC_LootDropManager : public UActorComponent
{
    GENERATED_BODY()

public:    
    UAC_LootDropManager();

    UPROPERTY(BlueprintAssignable, Category = "Loot")
    FOnItemReadyForSpawn OnItemReadyForSpawn;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Loot")
    TSoftObjectPtr<UDataTable> LootTable;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Loot")
    FLootItem OverrideItem;

    UFUNCTION(BlueprintCallable, Category = "Loot")
    void PickItem();

    UFUNCTION(BlueprintCallable, Category = "Loot")
    FLootItem GetRandomItemFromTable(UDataTable* Table);

    UFUNCTION(BlueprintPure, Category = "Loot")
    bool IsOverrideItemValid() const;
};
