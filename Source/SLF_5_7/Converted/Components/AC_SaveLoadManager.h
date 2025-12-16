#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "InstancedStruct.h"
#include "Structs/FSaveGameInfo.h"
#include "Classes/SG_SoulslikeFramework.h"
#include "AC_SaveLoadManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDataLoaded, FSaveGameInfo, LoadedData);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSaveComplete);

UCLASS( ClassGroup=(Custom), Blueprintable, meta=(BlueprintSpawnableComponent) )
class SLF_5_7_API UAC_SaveLoadManager : public UActorComponent
{
    GENERATED_BODY()

public:
    UAC_SaveLoadManager();

    // ============================================================
    // PROPERTIES
    // ============================================================

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SaveSystem")
    FString CurrentSaveSlot;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SaveSystem")
    TObjectPtr<USG_SoulslikeFramework> CurrentSaveGameObject;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SaveSystem")
    FSaveGameInfo Data;

    // ============================================================
    // DELEGATES
    // ============================================================

    UPROPERTY(BlueprintAssignable, Category = "SaveSystem")
    FOnDataLoaded OnDataLoaded;

    UPROPERTY(BlueprintAssignable, Category = "SaveSystem")
    FOnSaveComplete OnSaveComplete;

    // ============================================================
    // INITIALIZATION
    // ============================================================

    UFUNCTION(BlueprintCallable, Category = "SaveSystem|Initialization")
    void UpdateActiveSlot();

    UFUNCTION(BlueprintCallable, Category = "SaveSystem|Initialization")
    void TryPreloadData();

    UFUNCTION(BlueprintPure, Category = "SaveSystem|Initialization")
    FString GetActiveSlotName() const;

    // ============================================================
    // SAVE/LOAD
    // ============================================================

    UFUNCTION(BlueprintCallable, Category = "SaveSystem")
    void SaveData(const FSaveGameInfo& DataToSave);

    UFUNCTION(BlueprintCallable, Category = "SaveSystem")
    void LoadData();

    UFUNCTION(BlueprintCallable, Category = "SaveSystem")
    void LoadDataAsync();

    UFUNCTION(BlueprintCallable, Category = "SaveSystem")
    void ShowSavingVisual();

    UFUNCTION(BlueprintCallable, Category = "SaveSystem")
    void AddAndSaveSlots();

    // ============================================================
    // SERIALIZATION
    // ============================================================

    UFUNCTION(BlueprintCallable, Category = "SaveSystem|Serialization")
    void AddToSaveData(FGameplayTag SaveGameTag, const FInstancedStruct& DataToSave);

    UFUNCTION(BlueprintCallable, Category = "SaveSystem|Serialization")
    bool GetDataByTag(FGameplayTag SaveGameTag, FInstancedStruct& OutData);

    UFUNCTION(BlueprintCallable, Category = "SaveSystem|Serialization")
    void RefreshData();

    UFUNCTION(BlueprintPure, Category = "SaveSystem|Serialization")
    bool IsSaveDataValid() const;

protected:
    virtual void BeginPlay() override;

    // Async loading callback
    void OnAsyncLoadComplete(const FString& SlotName, int32 UserIndex, USaveGame* LoadedSave);
};
