#pragma once

#include "CoreMinimal.h"
#include "B_Interactable.h"
#include "Structs/FLootItem.h"
#include "B_PickupItem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnItemLooted);

UCLASS()
class SLF_5_7_API AB_PickupItem : public AB_Interactable
{
    GENERATED_BODY()
    
public:    
    AB_PickupItem();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Loot", meta = (ExposeOnSpawn = "true"))
    FLootItem Content;

    UPROPERTY(BlueprintAssignable, Category = "Loot")
    FOnItemLooted OnItemLooted;

    // Logic
    virtual void OnInteract_Implementation(AActor* InteractingActor) override;

protected:
    virtual void BeginPlay() override;
};
