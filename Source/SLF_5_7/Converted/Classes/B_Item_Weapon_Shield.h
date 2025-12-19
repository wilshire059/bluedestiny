#pragma once

#include "CoreMinimal.h"
#include "B_Weapon.h"
#include "GameplayTagContainer.h"
#include "Structs/FWeaponAttackPower.h"
#include "Enums/E_StatScaling.h"
#include "B_Item_Weapon_Shield.generated.h"

class UAC_StatManager;
class UAC_AI_CombatManager;
class UB_Stat;

UCLASS(Blueprintable)
class SLF_5_7_API AB_Item_Weapon_Shield : public AB_Weapon
{
    GENERATED_BODY()

public:
    AB_Item_Weapon_Shield();

    // ============================================================
    // PROPERTIES
    // ============================================================

    // Shield properties can be added here if needed

    // ============================================================
    // WEAPON INTERFACE FUNCTIONS
    // ============================================================

    // Get weapon status effect data
    UFUNCTION(BlueprintCallable, Category = "Weapon|Shield")
    TMap<FGameplayTag, int32> GetWeaponStatusEffectData() const;

    // Get weapon poise damage (shields typically have low poise damage)
    UFUNCTION(BlueprintCallable, Category = "Weapon|Shield")
    double GetWeaponPoiseDamage() const;

    // Get weapon attack power data from item info
    UFUNCTION(BlueprintCallable, Category = "Weapon|Shield")
    FWeaponAttackPower GetWeaponAttackPowerData() const;

    // Get weapon stat scaling information
    UFUNCTION(BlueprintCallable, Category = "Weapon|Shield")
    TMap<FGameplayTag, double> GetWeaponStatScaling() const;

    // Get a specific weapon stat value
    UFUNCTION(BlueprintCallable, Category = "Weapon|Shield")
    double GetWeaponStat(FGameplayTag StatTag) const;

    // Get attack power stats from instigator's stats
    UFUNCTION(BlueprintCallable, Category = "Weapon|Shield")
    FWeaponAttackPower GetAttackPowerStats() const;

    // ============================================================
    // COMBAT FUNCTIONS
    // ============================================================

    // Apply damage to an actor (called by collision manager)
    virtual void TryApplyDamage(AActor* DamagedActor, FHitResult Hit, double Multiplier) override;

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
    virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

    // Construction Script
    virtual void OnConstruction(const FTransform& Transform) override;

    // ============================================================
    // EVENT IMPLEMENTATIONS
    // ============================================================

    // Called when weapon is equipped
    virtual void OnWeaponEquip_Implementation(bool bRightHand) override;

    // Called when weapon is unequipped
    virtual void OnWeaponUnequip_Implementation() override;

    // Called when item is used
    virtual void OnUse_Implementation() override;

    // ============================================================
    // COLLISION DELEGATE HANDLER
    // ============================================================

    UFUNCTION()
    void OnActorTracedHandler(AActor* Actor, FHitResult Hit, double Multiplier);

private:
    // Helper to convert stat scaling enum to numeric value
    double GetScalingValue(E_StatScaling Scaling) const;
};
