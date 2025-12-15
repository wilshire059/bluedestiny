#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameplayTagContainer.h"
#include "StructUtils/InstancedStruct.h"
#include "Structs/FStatInfo.h"
#include "Enums/E_Direction.h"
#include "BPI_Controller.generated.h"

class UUserWidget;
class AActor;
class APawn;
class UMaterialInterface;
class UInputMappingContext;
class AB_PickupItem;
class UAC_InventoryManager;
class UAC_ProgressManager;
// class APC_SoulslikeFramework; // Assuming this class exists or will exist

UINTERFACE(MinimalAPI)
class UBPI_Controller : public UInterface
{
    GENERATED_BODY()
};

class SLF_5_7_API IBPI_Controller
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Controller")
    UUserWidget* GetPlayerHUD();

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Controller")
    void RequestAddToSaveData(FGameplayTag SaveTag, const FInstancedStruct& Data);

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Controller")
    void SetActiveWidgetForNavigation(FGameplayTag NavigableWidgetTag);

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Controller")
    void RequestUpdateSaveData(FGameplayTag SaveTag, const TArray<FInstancedStruct>& Data);

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Controller")
    void StartRespawn(double FadeDelay);

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Controller")
    void SendBigScreenMessage(const FText& Text, UMaterialInterface* GradientMaterial, bool bBackdrop, double PlayRate);

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Controller")
    int32 GetCurrency();

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Controller")
    void AdjustCurrency(int32 Delta);

    // E_SaveBehavior enum needed? Assuming int or byte for now if not found
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Controller")
    void SerializeDataForSaving(uint8 Behavior, FGameplayTag SaveTag);

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Controller")
    void ShowSavingVisual(double Length);

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Controller")
    void SwitchInputContext(const TArray<UInputMappingContext*>& ContextsToEnable, const TArray<UInputMappingContext*>& ContextsToDisable);

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Controller")
    UAC_ProgressManager* GetProgressManager();

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Controller")
    void BlendViewTarget(AActor* TargetActor, double BlendTime, double BlendExp, bool bLockOutgoing);

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Controller")
    void ToggleRadarUpdateState(bool bUpdateEnabled);

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Controller")
    void SerializeAllDataForSaving(uint8 Behavior);

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Controller")
    APlayerController* GetSoulslikeController(); // Return basic PC for now if specific class largely undefined

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Controller")
    void ToggleInput(bool bEnabled);

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Controller")
    APawn* GetPawnFromController();

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Controller")
    void LootItemToInventory(AB_PickupItem* Item);

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Controller")
    UAC_InventoryManager* GetInventoryComponent();
};
