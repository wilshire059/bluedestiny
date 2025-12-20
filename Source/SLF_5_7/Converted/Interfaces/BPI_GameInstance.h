#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DataAssets/PDA_CustomSettings.h"
#include "BPI_GameInstance.generated.h"

// Forward define
class USG_SoulslikeFramework;
class UGI_SoulslikeFramework;
class UPDA_BaseCharacterInfo;

// Interface
UINTERFACE(MinimalAPI)
class UBPI_GameInstance : public UInterface
{
    GENERATED_BODY()
};

class SLF_5_7_API IBPI_GameInstance
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Game Instance")
    void GetCustomGameSettings(UPDA_CustomSettings*& CustomSettingsAsset);

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Game Instance")
    void GetAllSaveSlots(TArray<FString>& SaveSlots);

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Game Instance")
    void SetLastSlotNameToActive();

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Game Instance")
    bool DoesAnySaveExist();

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Game Instance")
    void AddAndSaveSlots(const FString& NewSlotName);

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Game Instance")
    void GetActiveSlotName(FString& ActiveSlotName);

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Game Instance")
    void SetActiveSlot(const FString& ActiveSlotName);

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Game Instance")
    void GetSelectedClass(UPDA_BaseCharacterInfo*& SelectedBaseCharacterClass);

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Game Instance")
    void SetSelectedClass(UPDA_BaseCharacterInfo* BaseCharacterClass);

    /** Get the Soulslike game instance (matches Blueprint signature) */
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Game Instance")
    UGI_SoulslikeFramework* GetSoulslikeGameInstance();
};
