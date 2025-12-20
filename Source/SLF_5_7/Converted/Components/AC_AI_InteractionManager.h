#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "Engine/DataTable.h"
#include "Enums/E_Progress.h"
#include "Structs/FDialogEntry.h"
#include "Structs/FDialogGameplayEvent.h"
#include "AC_AI_InteractionManager.generated.h"

class UPDA_Dialog;
class UPDA_Vendor;
class UAC_ProgressManager;
class UAC_InventoryManager;
class UW_HUD;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDialogFinished);

UCLASS(ClassGroup = (Custom), Blueprintable, meta = (BlueprintSpawnableComponent))
class SLF_5_7_API UAC_AI_InteractionManager : public UActorComponent
{
    GENERATED_BODY()

public:
    UAC_AI_InteractionManager();

    // ============================================================
    // PROPERTIES - NPC INFO
    // ============================================================

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction|NPC")
    FText Name;

    // ============================================================
    // PROPERTIES - DIALOG
    // ============================================================

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction|Dialog")
    TObjectPtr<UPDA_Dialog> DialogAsset;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction|Dialog")
    TSoftObjectPtr<UDataTable> ActiveTable;

    UPROPERTY(BlueprintReadWrite, Category = "Interaction|Dialog")
    int32 CurrentIndex;

    UPROPERTY(BlueprintReadWrite, Category = "Interaction|Dialog")
    int32 MaxIndex;

    // ============================================================
    // PROPERTIES - VENDOR
    // ============================================================

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction|Vendor")
    TObjectPtr<UPDA_Vendor> VendorAsset;

    // ============================================================
    // PROPERTIES - REFERENCES
    // ============================================================

    UPROPERTY(BlueprintReadWrite, Category = "Interaction|References")
    TObjectPtr<UAC_ProgressManager> ProgressManager;

    // ============================================================
    // DELEGATES
    // ============================================================

    UPROPERTY(BlueprintAssignable, Category = "Interaction")
    FOnDialogFinished OnDialogFinished;

    // ============================================================
    // CUSTOM EVENTS (BlueprintCallable)
    // ============================================================

    UFUNCTION(BlueprintCallable, Category = "Interaction|Dialog")
    void Event_BeginDialog(UAC_ProgressManager* InProgressManager, UW_HUD* HUD);

    UFUNCTION(BlueprintCallable, Category = "Interaction|Dialog")
    void Event_AdjustIndexForExit();

    UFUNCTION(BlueprintCallable, Category = "Interaction|Dialog")
    void Event_ResetDialogIndex();

    // ============================================================
    // DIALOG FUNCTIONS
    // ============================================================

    UFUNCTION(BlueprintCallable, Category = "Interaction|Dialog")
    void GetCurrentDialogEntry(UDataTable* DataTable, const TArray<FName>& Rows, FDialogEntry& OutRow);

protected:
    virtual void BeginPlay() override;

private:
    // Helper function for async table loading (Event_BeginDialog)
    void OnDialogTableLoadedForBeginDialog(TSoftObjectPtr<UDataTable> LoadedTable, UAC_ProgressManager* InProgressManager, UW_HUD* HUD);

    // Helper function for async table loading (Event_AdjustIndexForExit)
    void OnDialogTableLoadedForAdjustIndex(TSoftObjectPtr<UDataTable> LoadedTable);
};
