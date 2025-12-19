#include "B_Item_Weapon.h"
#include "Components/AC_StatManager.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

AB_Item_Weapon::AB_Item_Weapon()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AB_Item_Weapon::BeginPlay()
{
    Super::BeginPlay();
}

void AB_Item_Weapon::OnWeaponEquip_Implementation(bool bRightHand)
{
    // Call parent implementation which handles attaching to socket
    Super::OnWeaponEquip_Implementation(bRightHand);

    // Additional weapon-specific equip logic can go here
}

TMap<int32, FStatusEffectApplication> AB_Item_Weapon::GetWeaponStatusEffectData() const
{
    TMap<int32, FStatusEffectApplication> StatusEffectInfo;

    // Access weapon status effect data from ItemInfo
    // The actual data structure would be stored in ItemInfo's equipment details
    // This is a placeholder that would need to be populated based on the actual struct layout

    return StatusEffectInfo;
}

double AB_Item_Weapon::GetWeaponPoiseDamage() const
{
    // Get base poise damage from ItemInfo
    // In the Blueprint, this appears to use a random range
    // For now, returning a base value that should be configured in ItemInfo
    double BasePoiseDamage = 10.0;

    // The Blueprint implementation uses RandomFloatInRange
    // This would typically be called during damage application
    double MinPoise = BasePoiseDamage * 0.9;
    double MaxPoise = BasePoiseDamage * 1.1;

    return UKismetMathLibrary::RandomFloatInRange(MinPoise, MaxPoise);
}

void AB_Item_Weapon::GetWeaponAttackPowerData(FWeaponAttackPower& OutAttackPower) const
{
    // Get base attack power from ItemInfo
    // This should be stored in ItemInfo.EquipmentDetails

    // Initialize with base values
    OutAttackPower.PhysicalDamage = 0.0f;
    OutAttackPower.MagicDamage = 0.0f;
    OutAttackPower.FireDamage = 0.0f;
    OutAttackPower.LightningDamage = 0.0f;
    OutAttackPower.HolyDamage = 0.0f;
    OutAttackPower.FrostDamage = 0.0f;

    // TODO: Extract from ItemInfo when the complete struct is available
    // For now, this would need to be manually configured via Blueprint defaults
}

TMap<FGameplayTag, uint8> AB_Item_Weapon::GetWeaponStatScaling() const
{
    TMap<FGameplayTag, uint8> Scaling;

    // Access scaling data from ItemInfo.EquipmentDetails.WeaponStatInfo.ScalingInfo
    const FEquipmentInfo& EquipDetails = ItemInfo.EquipmentDetails;
    const FEquipmentWeaponStatInfo& WeaponStats = EquipDetails.WeaponStatInfo;

    if (WeaponStats.bHasStatScaling)
    {
        // Convert the E_StatCategory map to GameplayTag map
        // This would require a mapping function or data table
        // For now, returning empty map as placeholder
    }

    return Scaling;
}

void AB_Item_Weapon::GetAttackPowerStats(FWeaponAttackPower& OutAttackPower)
{
    // Get the instigator's stat manager to calculate attack power with stat scaling
    APawn* InstigatorPawn = GetInstigator();
    if (!InstigatorPawn)
    {
        GetWeaponAttackPowerData(OutAttackPower);
        return;
    }

    UAC_StatManager* StatManager = InstigatorPawn->FindComponentByClass<UAC_StatManager>();
    if (!StatManager)
    {
        GetWeaponAttackPowerData(OutAttackPower);
        return;
    }

    // Start with base weapon attack power
    GetWeaponAttackPowerData(OutAttackPower);

    // Get weapon stat scaling
    TMap<FGameplayTag, uint8> ScalingMap = GetWeaponStatScaling();

    // Apply stat scaling to each damage type
    // This is a simplified version - the Blueprint has complex logic for each stat
    // and how it affects different damage types based on scaling grade

    // TODO: Implement full stat scaling calculation
    // This would involve:
    // 1. Getting each relevant stat value from StatManager
    // 2. Applying scaling grade multiplier
    // 3. Adding scaled value to appropriate damage type

    // For now, just return base values
}

void AB_Item_Weapon::TryApplyDamage(AActor* DamagedActor, FHitResult Hit, double Multiplier)
{
    if (!DamagedActor || DamagedActor == this || DamagedActor == GetInstigator())
    {
        return;
    }

    // Calculate total attack power including stat scaling
    FWeaponAttackPower AttackPower;
    GetAttackPowerStats(AttackPower);

    // Calculate total damage from all sources
    float TotalDamage = AttackPower.PhysicalDamage
                      + AttackPower.MagicDamage
                      + AttackPower.FireDamage
                      + AttackPower.LightningDamage
                      + AttackPower.HolyDamage
                      + AttackPower.FrostDamage;

    // Apply multiplier
    TotalDamage *= Multiplier;

    // Apply damage
    UGameplayStatics::ApplyPointDamage(
        DamagedActor,
        TotalDamage,
        Hit.ImpactNormal,
        Hit,
        GetInstigatorController(),
        this,
        UDamageType::StaticClass()
    );

    // TODO: Apply status effects from GetWeaponStatusEffectData
    // TODO: Apply poise damage from GetWeaponPoiseDamage
}

FWeaponAttackPower AB_Item_Weapon::CalculateTotalAttackPower() const
{
    FWeaponAttackPower TotalPower;
    GetWeaponAttackPowerData(TotalPower);

    // This would be expanded to include stat scaling calculations
    // Similar to GetAttackPowerStats but as a const helper

    return TotalPower;
}

double AB_Item_Weapon::GetStatValue(const FGameplayTag& StatTag) const
{
    APawn* InstigatorPawn = GetInstigator();
    if (!InstigatorPawn)
    {
        return 0.0;
    }

    UAC_StatManager* StatManager = InstigatorPawn->FindComponentByClass<UAC_StatManager>();
    if (!StatManager)
    {
        return 0.0;
    }

    UB_Stat* Stat = StatManager->GetStat(StatTag);
    if (!Stat)
    {
        return 0.0;
    }

    // TODO: Get the actual value from the Stat object
    // This would require checking B_Stat.h for the proper accessor
    return 0.0;
}
