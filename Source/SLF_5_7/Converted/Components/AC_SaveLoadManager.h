#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Structs/FSaveGameInfo.h"
#include "Classes/SG_SoulslikeFramework.h"
#include "AC_SaveLoadManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDataLoaded, FSaveGameInfo, LoadedData);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SLF_5_7_API UAC_SaveLoadManager : public UActorComponent
{
    GENERATED_BODY()

public:    
    UAC_SaveLoadManager();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SaveSystem")
    FString CurrentSaveSlot;

    // Delegates
    UPROPERTY(BlueprintAssignable, Category = "SaveSystem")
    FOnDataLoaded OnDataLoaded;

    // Functions
    UFUNCTION(BlueprintCallable, Category = "SaveSystem")
    void SaveData(const FSaveGameInfo& DataToSave);

    UFUNCTION(BlueprintCallable, Category = "SaveSystem")
    void LoadData();

    UFUNCTION(BlueprintCallable, Category = "SaveSystem")
    void TryPreloadData();

    UFUNCTION(BlueprintCallable, Category = "SaveSystem")
    void UpdateActiveSlot();

protected:
    virtual void BeginPlay() override;
};
