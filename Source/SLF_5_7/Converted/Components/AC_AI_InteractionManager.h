#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "Engine/DataTable.h"
#include "Enums/E_Progress.h"
#include "AC_AI_InteractionManager.generated.h"

class UPDA_Dialog;
class UAC_ProgressManager;
class UAC_InventoryManager;
class UUserWidget;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDialogStarted, UDataTable*, DialogTable);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDialogEnded);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnDialogEntryChanged, int32, EntryIndex, FName, RowName);

UCLASS(ClassGroup = (Custom), Blueprintable, meta = (BlueprintSpawnableComponent))
class SLF_5_7_API UAC_AI_InteractionManager : public UActorComponent
{
    GENERATED_BODY()

public:
    UAC_AI_InteractionManager();

    // ============================================================
    // PROPERTIES - DIALOG
    // ============================================================

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction|Dialog")
    TObjectPtr<UPDA_Dialog> DialogAsset;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction|Dialog")
    TObjectPtr<UDataTable> ActiveDialogTable;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction|Dialog")
    TArray<FName> DialogRows;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction|Dialog")
    int32 CurrentIndex;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction|Dialog")
    bool bDialogActive;

    // ============================================================
    // PROPERTIES - REFERENCES
    // ============================================================

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction|References")
    TObjectPtr<UAC_ProgressManager> ProgressManager;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction|References")
    TObjectPtr<UUserWidget> HUDWidget;

    // ============================================================
    // DELEGATES
    // ============================================================

    UPROPERTY(BlueprintAssignable, Category = "Interaction")
    FOnDialogStarted OnDialogStarted;

    UPROPERTY(BlueprintAssignable, Category = "Interaction")
    FOnDialogEnded OnDialogEnded;

    UPROPERTY(BlueprintAssignable, Category = "Interaction")
    FOnDialogEntryChanged OnDialogEntryChanged;

    // ============================================================
    // DIALOG FUNCTIONS
    // ============================================================

    UFUNCTION(BlueprintCallable, Category = "Interaction|Dialog")
    void BeginDialog(UAC_ProgressManager* InProgressManager, UUserWidget* InHUD);

    UFUNCTION(BlueprintCallable, Category = "Interaction|Dialog")
    void EndDialog();

    UFUNCTION(BlueprintCallable, Category = "Interaction|Dialog")
    void AdvanceDialog();

    UFUNCTION(BlueprintCallable, Category = "Interaction|Dialog")
    bool GetCurrentDialogEntry(UDataTable* DataTable, const TArray<FName>& Rows, FName& OutRowName);

    UFUNCTION(BlueprintPure, Category = "Interaction|Dialog")
    bool IsDialogActive() const;

    // ============================================================
    // PROGRESS FUNCTIONS
    // ============================================================

    UFUNCTION(BlueprintCallable, Category = "Interaction|Progress")
    void SetProgress(FGameplayTag ProgressTag, E_Progress State);

    UFUNCTION(BlueprintPure, Category = "Interaction|Progress")
    E_Progress GetProgress(FGameplayTag ProgressTag) const;

    UFUNCTION(BlueprintPure, Category = "Interaction|Progress")
    UAC_ProgressManager* GetLocalProgressManager() const;

    // ============================================================
    // DIALOG TABLE FUNCTIONS
    // ============================================================

    UFUNCTION(BlueprintCallable, Category = "Interaction|Dialog")
    TSoftObjectPtr<UDataTable> GetDialogTableBasedOnProgress(UAC_ProgressManager* InProgressManager);

    // ============================================================
    // GAMEPLAY EVENTS
    // ============================================================

    UFUNCTION(BlueprintCallable, Category = "Interaction|Events")
    void ExecuteGameplayEvents(const TArray<FGameplayTag>& EventTags);

    // ============================================================
    // CURRENCY
    // ============================================================

    UFUNCTION(BlueprintCallable, Category = "Interaction|Currency")
    void AdjustCurrency(int32 Amount);

protected:
    virtual void BeginPlay() override;

    void OnDialogTableLoaded(TSoftObjectPtr<UDataTable> LoadedTable);
};
