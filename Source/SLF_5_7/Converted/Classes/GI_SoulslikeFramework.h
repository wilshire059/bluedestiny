#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interfaces/BPI_GameInstance.h"
#include "Structs/FSaveGameInfo.h"
#include "DataAssets/PDA_CustomSettings.h"
#include "DataAssets/PDA_BaseCharacterInfo.h"
#include "GI_SoulslikeFramework.generated.h"

// Delegate for when selected class changes
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSelectedClassChangedDelegate);

UCLASS()
class SLF_5_7_API UGI_SoulslikeFramework : public UGameInstance, public IBPI_GameInstance
{
    GENERATED_BODY()

public:
    UGI_SoulslikeFramework();

    virtual void Init() override;

    // -- Properties --
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
    UPDA_CustomSettings* CustomGameSettings;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterSelection")
    UPDA_BaseCharacterInfo* SelectedBaseClass;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnSelectedClassChangedDelegate OnSelectedClassChanged;

    UPROPERTY(BlueprintReadWrite, Category = "SaveSystem")
    class USG_SaveSlots* SGO_Slots;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SaveSystem")
    FString SlotsSaveName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SaveSystem")
    FString ActiveSlot;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug")
    bool bFirstTimeOnDemoLevel;

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
