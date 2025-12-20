// Copyright Epic Games, Inc. All Rights Reserved.
// Converted from Blueprint: B_Chaos_ForceField

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Field/FieldSystemComponent.h"
#include "Field/FieldSystemObjects.h"
#include "Components/SphereComponent.h"
#include "../Interfaces/BPI_DestructibleHelper.h"
#include "ChaosForceField.generated.h"

/**
 * Actor that creates a Chaos force field for destruction
 * Can be enabled/disabled via interface
 */
UCLASS(Blueprintable, BlueprintType)
class SLF_5_7_API AChaosForceField : public AActor, public IBPI_DestructibleHelper
{
	GENERATED_BODY()

public:
	AChaosForceField();

protected:
	/** Field system component for applying physics fields */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UFieldSystemComponent> FieldSystemComponent;

	/** Sphere component for defining field radius */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USphereComponent> Sphere;

	/** Radial falloff field object */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Field")
	TObjectPtr<URadialFalloff> RadialFalloff;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:
	// BPI_DestructibleHelper interface
	virtual void EnableChaosDestroy_Implementation() override;
	virtual void DisableChaosDestroy_Implementation() override;
};
