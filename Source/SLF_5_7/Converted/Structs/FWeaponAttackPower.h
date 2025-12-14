#pragma once

#include "CoreMinimal.h"
#include "FWeaponAttackPower.generated.h"

/**
 * Weapon attack power configuration.
 */
USTRUCT(BlueprintType)
struct SLF_5_7_API FWeaponAttackPower
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float PhysicalDamage = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float MagicDamage = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float FireDamage = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float LightningDamage = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float HolyDamage = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float FrostDamage = 0.0f;
};
