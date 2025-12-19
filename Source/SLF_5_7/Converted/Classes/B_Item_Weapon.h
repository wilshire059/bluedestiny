#pragma once

#include "CoreMinimal.h"
#include "B_Weapon.h"
#include "GameplayTagContainer.h"
#include "Structs/FStatusEffectApplication.h"
#include "Structs/FWeaponAttackPower.h"
#include "B_Item_Weapon.generated.h"

UCLASS(Blueprintable)
class SLF_5_7_API AB_Item_Weapon : public AB_Weapon
{
    GENERATED_BODY()

public:
    AB_Item_Weapon();

protected:
    virtual void BeginPlay() override;

public:
    // Override from parent
    virtual void OnWeaponEquip_Implementation(bool bRightHand) override;

    // Weapon stat and combat functions
    UFUNCTION(BlueprintPure, Category = "Weapon|Combat")
    TMap<int32, FStatusEffectApplication> GetWeaponStatusEffectData() const;

    UFUNCTION(BlueprintPure, Category = "Weapon|Combat")
    double GetWeaponPoiseDamage() const;

    UFUNCTION(BlueprintCallable, Category = "Weapon|Combat")
    void GetWeaponAttackPowerData(FWeaponAttackPower& OutAttackPower) const;

    UFUNCTION(BlueprintPure, Category = "Weapon|Combat")
    TMap<FGameplayTag, uint8> GetWeaponStatScaling() const;

    UFUNCTION(BlueprintCallable, Category = "Weapon|Combat")
    void GetAttackPowerStats(FWeaponAttackPower& OutAttackPower);

    // Override TryApplyDamage to use weapon-specific damage calculation
    void TryApplyDamage(AActor* DamagedActor, FHitResult Hit, double Multiplier);

protected:
    // Helper function to calculate total attack power including stat scaling
    FWeaponAttackPower CalculateTotalAttackPower() const;

    // Helper function to get stat value from instigator's stat manager
    double GetStatValue(const FGameplayTag& StatTag) const;
};
