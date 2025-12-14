#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Structs/FSLFItemInfo.h"
#include "BPI_Interactable.generated.h"

UINTERFACE(MinimalAPI)
class UBPI_Interactable : public UInterface
{
    GENERATED_BODY()
};

class SLF_5_7_API IBPI_Interactable
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interactable")
    void OnInteract(AActor* InteractingActor);

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interactable")
    void OnTraced(AActor* TracedBy);

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interactable")
    void TryGetItemInfo(FSLFItemInfo& ItemInfo);

    // TODO: OnSpawnedFromSave omittied because FInstancedStruct (StructUtils) is not enabled in .uproject
    // UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interactable")
    // void OnSpawnedFromSave(FGuid Id, FInstancedStruct CustomData);
};
