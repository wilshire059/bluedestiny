#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Structs/FSaveGameInfo.h"
#include "SG_SoulslikeFramework.generated.h"

/**
 * Save Game Object
 */
UCLASS()
class SLF_5_7_API USG_SoulslikeFramework : public USaveGame
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SaveData")
    FSaveGameInfo SavedData;

    UFUNCTION(BlueprintCallable, Category = "SaveData")
    FSaveGameInfo GetSavedData() const { return SavedData; }

    UFUNCTION(BlueprintCallable, Category = "SaveData")
    void SetSavedData(FSaveGameInfo InData) { SavedData = InData; }

    // JSON mentioned class defaults: SavedData = "()". Default constructor handles this.
};
