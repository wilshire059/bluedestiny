// Copyright Epic Games, Inc. All Rights Reserved.
// Converted from Blueprint: B_AbilityEffectBase

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AbilityEffectBase.generated.h"

/**
 * Base class for ability visual effects
 * Spawns, prints debug info, and destroys itself immediately
 */
UCLASS(Blueprintable, BlueprintType)
class SLF_5_7_API AAbilityEffectBase : public AActor
{
	GENERATED_BODY()

public:
	AAbilityEffectBase();

protected:
	/** Root component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USceneComponent> DefaultSceneRoot;

	virtual void BeginPlay() override;
};
