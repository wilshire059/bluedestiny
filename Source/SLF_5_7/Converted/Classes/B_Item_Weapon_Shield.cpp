#include "B_Item_Weapon_Shield.h"
#include "Components/AC_StatManager.h"
#include "Components/AC_AI_CombatManager.h"
#include "Components/AC_CombatManager.h"
#include "Components/AC_CollisionManager.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Classes/B_Stat.h"
#include "Structs/FSLFItemInfo.h"
#include "Structs/FEquipmentWeaponStatInfo.h"
#include "Structs/FStatInfo.h"
#include "Enums/E_StatCategory.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/Pawn.h"

AB_Item_Weapon_Shield::AB_Item_Weapon_Shield()
{
    PrimaryActorTick.bCanEverTick = true;

    // Shield-specific initialization
    // Shields typically have lower damage but better defense
}

void AB_Item_Weapon_Shield::BeginPlay()
{
    Super::BeginPlay();

    // Shield-specific initialization
    // Note: Parent class already binds OnActorTraced delegate
}

void AB_Item_Weapon_Shield::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Shield-specific tick logic if needed
}

void AB_Item_Weapon_Shield::NotifyActorBeginOverlap(AActor* OtherActor)
{
    Super::NotifyActorBeginOverlap(OtherActor);

    // Shield-specific overlap logic if needed
}

void AB_Item_Weapon_Shield::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);

    // UserConstructionScript logic
    // The JSON shows complex socket tracing and positioning logic
    // This would be used for visual feedback in the editor

    UPrimitiveComponent* Mesh = GetWeaponMesh();
    if (Mesh && Mesh->DoesSocketExist(TEXT("Top")) && Mesh->DoesSocketExist(TEXT("Bottom")))
    {
        FVector TopLocation = Mesh->GetSocketLocation(TEXT("Top"));
        FVector BottomLocation = Mesh->GetSocketLocation(TEXT("Bottom"));

        // Calculate distance for shield effect visualization
        FVector Difference = TopLocation - BottomLocation;
        double Distance = Difference.Size();

        // This would typically be used to set material parameters or visual effects
        // For now, we'll leave this as a placeholder
    }
}

TMap<FGameplayTag, int32> AB_Item_Weapon_Shield::GetWeaponStatusEffectData() const
{
    TMap<FGameplayTag, int32> StatusEffectData;

    // TODO: Get status effect data from ItemInfo or WeaponStatInfo
    // The actual status effect data structure is not yet defined in the current struct layout
    // This would typically come from a data asset or additional weapon properties

    return StatusEffectData;
}

double AB_Item_Weapon_Shield::GetWeaponPoiseDamage() const
{
    // Shields typically have low poise damage
    // The Blueprint shows this returns a random value
    // For now, we'll use a fixed value based on weapon stats

    double BasePoiseDamage = 0.0;

    // Get poise damage from weapon stats if available
    // This would typically come from the ItemInfo weapon stats

    return BasePoiseDamage;
}

FWeaponAttackPower AB_Item_Weapon_Shield::GetWeaponAttackPowerData() const
{
    FWeaponAttackPower AttackPower;

    // TODO: Get attack power from a data asset or weapon properties
    // The current FEquipmentInfo struct doesn't have an AttackPower field
    // This would typically come from a PDA_Weapon or similar data asset
    // For now, return zeros - this should be populated from weapon data assets

    AttackPower.PhysicalDamage = 0.0f;
    AttackPower.MagicDamage = 0.0f;
    AttackPower.FireDamage = 0.0f;
    AttackPower.LightningDamage = 0.0f;
    AttackPower.HolyDamage = 0.0f;
    AttackPower.FrostDamage = 0.0f;

    return AttackPower;
}

TMap<FGameplayTag, double> AB_Item_Weapon_Shield::GetWeaponStatScaling() const
{
    TMap<FGameplayTag, double> Scaling;

    // Get scaling from ItemInfo
    const FEquipmentWeaponStatInfo& WeaponStats = ItemInfo.EquipmentDetails.WeaponStatInfo;

    if (WeaponStats.bHasStatScaling)
    {
        // Convert E_StatCategory -> E_StatScaling map to GameplayTag -> double map
        TArray<E_StatCategory> Keys;
        WeaponStats.ScalingInfo.GetKeys(Keys);

        TArray<E_StatScaling> Values;
        WeaponStats.ScalingInfo.GenerateValueArray(Values);

        for (int32 i = 0; i < Keys.Num(); i++)
        {
            E_StatCategory StatCategory = Keys[i];
            E_StatScaling ScalingEnum = Values[i];

            // TODO: Convert stat category to gameplay tag
            // This would need a mapping function or lookup table
            FGameplayTag StatTag;

            // Convert scaling enum to numeric value
            double ScalingValue = GetScalingValue(ScalingEnum);

            if (StatTag.IsValid())
            {
                Scaling.Add(StatTag, ScalingValue);
            }
        }
    }

    return Scaling;
}

double AB_Item_Weapon_Shield::GetWeaponStat(FGameplayTag StatTag) const
{
    double StatValue = 0.0;

    if (!StatTag.IsValid())
    {
        return StatValue;
    }

    // TODO: Find the stat from weapon data or ItemInfo
    // The current struct layout doesn't have a direct AttackPower map
    // This would typically come from a weapon data asset

    return StatValue;
}

FWeaponAttackPower AB_Item_Weapon_Shield::GetAttackPowerStats() const
{
    FWeaponAttackPower AttackPower;

    // Get the instigator's stat manager
    APawn* OwnerPawn = GetInstigator();
    if (!OwnerPawn)
    {
        return AttackPower;
    }

    UAC_StatManager* StatManager = OwnerPawn->FindComponentByClass<UAC_StatManager>();
    if (!StatManager)
    {
        return AttackPower;
    }

    // Get stats for each damage type from the stat manager
    // Note: These tag names are assumed - adjust based on your actual tag structure

    UB_Stat* PhysicalStat = StatManager->GetStat(FGameplayTag::RequestGameplayTag(TEXT("Stat.AttackPower.Physical")));
    if (PhysicalStat)
    {
        FStatInfo StatInfo = PhysicalStat->GetStatInfo();
        AttackPower.PhysicalDamage = StatInfo.Value;
    }

    UB_Stat* MagicStat = StatManager->GetStat(FGameplayTag::RequestGameplayTag(TEXT("Stat.AttackPower.Magic")));
    if (MagicStat)
    {
        FStatInfo StatInfo = MagicStat->GetStatInfo();
        AttackPower.MagicDamage = StatInfo.Value;
    }

    UB_Stat* FireStat = StatManager->GetStat(FGameplayTag::RequestGameplayTag(TEXT("Stat.AttackPower.Fire")));
    if (FireStat)
    {
        FStatInfo StatInfo = FireStat->GetStatInfo();
        AttackPower.FireDamage = StatInfo.Value;
    }

    UB_Stat* LightningStat = StatManager->GetStat(FGameplayTag::RequestGameplayTag(TEXT("Stat.AttackPower.Lightning")));
    if (LightningStat)
    {
        FStatInfo StatInfo = LightningStat->GetStatInfo();
        AttackPower.LightningDamage = StatInfo.Value;
    }

    UB_Stat* HolyStat = StatManager->GetStat(FGameplayTag::RequestGameplayTag(TEXT("Stat.AttackPower.Holy")));
    if (HolyStat)
    {
        FStatInfo StatInfo = HolyStat->GetStatInfo();
        AttackPower.HolyDamage = StatInfo.Value;
    }

    UB_Stat* FrostStat = StatManager->GetStat(FGameplayTag::RequestGameplayTag(TEXT("Stat.AttackPower.Frost")));
    if (FrostStat)
    {
        FStatInfo StatInfo = FrostStat->GetStatInfo();
        AttackPower.FrostDamage = StatInfo.Value;
    }

    return AttackPower;
}

void AB_Item_Weapon_Shield::TryApplyDamage(AActor* DamagedActor, FHitResult Hit, double Multiplier)
{
    if (!DamagedActor || DamagedActor == this || DamagedActor == GetInstigator())
    {
        return;
    }

    // Get the instigator's stat manager and combat manager
    APawn* OwnerPawn = GetInstigator();
    if (!OwnerPawn)
    {
        return;
    }

    UAC_StatManager* StatManager = OwnerPawn->FindComponentByClass<UAC_StatManager>();
    if (!StatManager)
    {
        return;
    }

    // Get attack power stats
    FWeaponAttackPower AttackPowerData = GetAttackPowerStats();

    // Get weapon stat scaling
    TMap<FGameplayTag, double> Scaling = GetWeaponStatScaling();

    // Calculate weapon damage using the combat manager's calculation
    // For shields, the damage is typically lower than regular weapons
    UAC_AI_CombatManager* AICombatManager = DamagedActor->FindComponentByClass<UAC_AI_CombatManager>();
    if (AICombatManager)
    {
        // Get weapon status effects
        TMap<FGameplayTag, int32> StatusEffects = GetWeaponStatusEffectData();

        // Get weapon poise damage
        double PoiseDamage = GetWeaponPoiseDamage();

        // Calculate final damage
        // This is a simplified version - actual implementation would use CombatManager's CalculateWeaponDamage
        double BaseDamage = AttackPowerData.PhysicalDamage; // Use physical as base
        double FinalDamage = BaseDamage * Multiplier;

        // Apply damage through the damage system
        UGameplayStatics::ApplyPointDamage(
            DamagedActor,
            FinalDamage,
            Hit.ImpactNormal,
            Hit,
            GetInstigatorController(),
            this,
            UDamageType::StaticClass()
        );
    }
}

void AB_Item_Weapon_Shield::OnWeaponEquip_Implementation(bool bRightHand)
{
    Super::OnWeaponEquip_Implementation(bRightHand);

    // Shield-specific equip logic
}

void AB_Item_Weapon_Shield::OnWeaponUnequip_Implementation()
{
    Super::OnWeaponUnequip_Implementation();

    // Shield-specific unequip logic
}

void AB_Item_Weapon_Shield::OnUse_Implementation()
{
    Super::OnUse_Implementation();

    // Shield-specific use logic (e.g., activate parry)
}

void AB_Item_Weapon_Shield::OnActorTracedHandler(AActor* Actor, FHitResult Hit, double Multiplier)
{
    TryApplyDamage(Actor, Hit, Multiplier);
}

double AB_Item_Weapon_Shield::GetScalingValue(E_StatScaling Scaling) const
{
    // Convert scaling enum to numeric value
    // Based on the JSON, these appear to be literal double values
    switch (Scaling)
    {
        case E_StatScaling::S:
            return 0.90; // 90% scaling
        case E_StatScaling::A:
            return 0.75; // 75% scaling
        case E_StatScaling::B:
            return 0.60; // 60% scaling
        case E_StatScaling::C:
            return 0.45; // 45% scaling
        case E_StatScaling::D:
            return 0.30; // 30% scaling
        case E_StatScaling::E:
            return 0.15; // 15% scaling
        default:
            return 0.0;
    }
}
