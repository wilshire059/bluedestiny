#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BPI_Player.generated.h"

// Forward Declaration
class AB_Interactable;

UINTERFACE(MinimalAPI)
class UBPI_Player : public UInterface
{
    GENERATED_BODY()
};

class SLF_5_7_API IBPI_Player
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Player")
    void OnInteractableTraced(AB_Interactable* Interactable);

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Player")
    void OnRest(AActor* Campfire);

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Player")
    void OnLootItem(AActor* Item); // Passing AActor (B_PickupItem)

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Player")
    void TriggerChaosField(bool bEnable);
};
