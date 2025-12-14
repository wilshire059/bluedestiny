#pragma once

#include "CoreMinimal.h"
#include "B_Interactable.h"
#include "Components/TimelineComponent.h"
#include "Components/PointLightComponent.h"
#include "Components/BillboardComponent.h"
#include "AC_LootDropManager.h"
#include "B_Container.generated.h"

UCLASS()
class SLF_5_7_API AB_Container : public AB_Interactable
{
    GENERATED_BODY()

public:
    AB_Container();

    // Components
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<UStaticMeshComponent> Lid;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<UPointLightComponent> PointLight;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<UBillboardComponent> ItemSpawn;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<UAC_LootDropManager> LootDropManager;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<UTimelineComponent> OpenChest;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<UTimelineComponent> FadeOffTimeline;

    // Variables
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Container")
    double SpeedMultiplier;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Container")
    TSoftObjectPtr<UAnimMontage> OpenMontage;

    // Timeline Updates
    FOnTimelineFloat UpdateOpenChest;
    FOnTimelineEvent FinishedOpenChest;
    FOnTimelineEvent ItemSpawnEvent;
    FOnTimelineEvent SpawnVFXEvent;

    FOnTimelineFloat UpdateFadeOff;
    FOnTimelineEvent FinishedFadeOff;

    // Logic
    virtual void OnInteract_Implementation(AActor* InteractingActor) override;

    UFUNCTION(BlueprintCallable, Category = "Container")
    void OpenContainer();

    UFUNCTION()
    void OnSpawnedItemLooted();

    UFUNCTION()
    void OnLootReady(FLootItem Item);

    // Timeline Callbacks
    UFUNCTION()
    void OnOpenChestUpdate(float Value);
    
    UFUNCTION()
    void OnOpenChestFinished();
    
    UFUNCTION()
    void OnItemSpawnEvent();
    
    UFUNCTION()
    void OnSpawnVFXEvent();

    UFUNCTION()
    void OnFadeOffUpdate(float Value);

protected:
    virtual void BeginPlay() override;
};
