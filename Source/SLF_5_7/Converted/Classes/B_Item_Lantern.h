#pragma once

#include "CoreMinimal.h"
#include "B_Item.h"
#include "Components/PointLightComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TimelineComponent.h"
#include "B_Item_Lantern.generated.h"

/**
 * Lantern item that can be used to provide light
 * Implements the OnUse interface to activate the lantern
 * Features:
 * - Attaches to player's LanternSocket when used
 * - Has a configurable lifetime (LanternLife)
 * - Fades off over time before destroying
 * - Uses two lights (RimLight and AreaLight) for visual effect
 */
UCLASS(Blueprintable)
class SLF_5_7_API AB_Item_Lantern : public AB_Item
{
    GENERATED_BODY()

public:
    AB_Item_Lantern();

    // ============================================================
    // COMPONENTS
    // ============================================================

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<UStaticMeshComponent> StaticMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<UPointLightComponent> AreaLight;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<UPointLightComponent> RimLight;

    // ============================================================
    // PROPERTIES
    // ============================================================

    // How long the lantern stays active (in seconds)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lantern")
    float LanternLife;

    // ============================================================
    // PUBLIC FUNCTIONS
    // ============================================================

    // Start the fadeoff timeline
    UFUNCTION(BlueprintCallable, Category = "Lantern")
    void StartFadeoff();

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

    // ============================================================
    // INTERFACE IMPLEMENTATIONS
    // ============================================================

    // Called when the item is used
    virtual void OnUse_Implementation() override;

    // ============================================================
    // CUSTOM EVENTS
    // ============================================================

    // Called when the lantern lifetime ends and fadeoff begins
    UFUNCTION()
    void LanternFinished();

    // Called after fadeoff completes to destroy the lantern
    UFUNCTION()
    void DestroyLantern();

    // ============================================================
    // TIMELINE SIMULATION
    // ============================================================

    // Timeline for fading off the lantern lights
    bool bIsFadingOff;
    float FadeoffAlpha;
    float FadeoffDuration;

    // Timer handle for lantern lifetime
    FTimerHandle LanternLifetimeTimer;

    // Timer handle for destruction after fadeoff
    FTimerHandle DestroyTimer;

    // Reference material for when lantern is off
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lantern|Materials")
    TObjectPtr<UMaterialInterface> LanternOffMaterial;
};
