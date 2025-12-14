// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Animation/AnimationAsset.h"
#include "PDA_AnimData.generated.h"

/**
 * Data Asset for Animation Data (Locomotion, Idle, etc).
 */
UCLASS(BlueprintType)
class SLF_5_7_API UPDA_AnimData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPDA_AnimData();

	/** Walk/Run Locomotion (BlendSpace or Sequence) */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Locomotion")
	TSoftObjectPtr<UAnimationAsset> WalkRunLocomotion;

	/** Crouch Locomotion */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Locomotion")
	TSoftObjectPtr<UAnimationAsset> CrouchLocomotion;

	/** One Handed Weapon Left */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapons")
	TSoftObjectPtr<UAnimationAsset> OneHandedWeapon_Left;

	/** One Handed Weapon Right */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapons")
	TSoftObjectPtr<UAnimationAsset> OneHandedWeapon_Right;

	/** Dual Wield */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapons")
	TSoftObjectPtr<UAnimationAsset> DualWield;

	/** Two Handed Weapon Right */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapons")
	TSoftObjectPtr<UAnimationAsset> TwoHandedWeapon_Right;

	/** Two Handed Weapon Left */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapons")
	TSoftObjectPtr<UAnimationAsset> TwoHandedWeapon_Left;

	/** Shield Left */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapons")
	TSoftObjectPtr<UAnimationAsset> ShieldLeft;

	/** Idle Animation */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Idle")
	TSoftObjectPtr<UAnimationAsset> Idle;

	/** Crouch Idle Animation */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Idle")
	TSoftObjectPtr<UAnimationAsset> CrouchIdle;

	/** Resting Idle Animation */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Idle")
	TSoftObjectPtr<UAnimationAsset> RestingIdle;

	/** Debug flag */
	UPROPERTY(EditAnywhere, Category = "Debug")
	bool DEBUG_DEFAULT_CHECK = true;
};
