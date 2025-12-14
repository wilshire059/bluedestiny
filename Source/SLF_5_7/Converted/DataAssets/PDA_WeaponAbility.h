#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "PDA_WeaponAbility.generated.h"

UCLASS(BlueprintType)
class SLF_5_7_API UPDA_WeaponAbility : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPDA_WeaponAbility();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Ability")
	TSoftObjectPtr<UTexture2D> Icon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Ability")
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Ability")
	FGameplayTag AffectedStat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Ability")
	double Cost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Ability")
	TSoftObjectPtr<UAnimMontage> Montage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Ability", meta = (AllowAbstract = "true"))
	TSoftClassPtr<AActor> AdditionalEffectClass;
};
