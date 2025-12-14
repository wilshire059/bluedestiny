#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interfaces/BPI_GameInstance.h"
#include "Structs/FSaveGameInfo.h"
#include "DataAssets/PDA_CustomSettings.h"
#include "DataAssets/PDA_BaseCharacterInfo.h"
#include "GI_SoulslikeFramework.generated.h"

UCLASS()
class SLF_5_7_API UGI_SoulslikeFramework : public UGameInstance, public IBPI_GameInstance
{
    GENERATED_BODY()

public:
    UGI_SoulslikeFramework();

    // -- Properties --
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
    UPDA_CustomSettings* CustomSettings;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SaveSystem")
    TArray<FString> SaveSlots;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SaveSystem")
    FString ActiveSlotName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterSelection")
    UPDA_BaseCharacterInfo* SelectedBaseCharacterClass;

    // -- Interface Implementation --
    virtual void GetCustomGameSettings_Implementation(UPDA_CustomSettings*& CustomSettingsAsset) override;
    virtual void GetAllSaveSlots_Implementation(TArray<FString>& OutSaveSlots) override;
    virtual void SetLastSlotNameToActive_Implementation() override;
    virtual bool DoesAnySaveExist_Implementation() override;
    virtual void AddAndSaveSlots_Implementation(const FString& NewSlotName) override;
    virtual void GetActiveSlotName_Implementation(FString& OutActiveSlotName) override;
    virtual void SetActiveSlot_Implementation(const FString& InActiveSlotName) override;
    virtual void GetSelectedClass_Implementation(UPDA_BaseCharacterInfo*& SelectedClass) override;
    virtual void SetSelectedClass_Implementation(UPDA_BaseCharacterInfo* BaseCharacterClass) override;
    
    // -- Save Management of Slot List --
    UFUNCTION(BlueprintCallable, Category = "SaveSystem")
    void SaveSlotList();
    
    UFUNCTION(BlueprintCallable, Category = "SaveSystem")
    void LoadSlotList();
};
