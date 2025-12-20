// Copyright Epic Games, Inc. All Rights Reserved.
// Converted from Blueprint: B_Chaos_ForceField

#include "ChaosForceField.h"

AChaosForceField::AChaosForceField()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bAllowTickOnDedicatedServer = true;
	PrimaryActorTick.bStartWithTickEnabled = false; // Start disabled

	// Create field system component as root
	FieldSystemComponent = CreateDefaultSubobject<UFieldSystemComponent>(TEXT("FieldSystemComponent"));
	RootComponent = FieldSystemComponent;

	// Create sphere component
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetupAttachment(RootComponent);

	// Create radial falloff field object
	RadialFalloff = CreateDefaultSubobject<URadialFalloff>(TEXT("RadialFalloff"));
}

void AChaosForceField::BeginPlay()
{
	Super::BeginPlay();

	// Initially disabled - tick is off by default
}

void AChaosForceField::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Apply transient field every tick when enabled
	if (FieldSystemComponent && RadialFalloff && Sphere)
	{
		// Get sphere center in world space
		const FVector SphereCenter = Sphere->GetComponentLocation();

		// Get sphere radius
		const float SphereRadius = Sphere->GetScaledSphereRadius();

		// Configure radial falloff
		RadialFalloff->SetRadialFalloff(
			99999999.0f,              // FieldMagnitude
			0.0f,                     // MinRange
			1.0f,                     // MaxRange
			0.0f,                     // DefaultValue
			SphereRadius,             // SphereRadius
			SphereCenter,             // CenterPosition
			EFieldFalloffType::Field_FallOff_None
		);

		// Apply physics field
		FieldSystemComponent->ApplyPhysicsField(
			true,                                      // EnableField
			EFieldPhysicsType::Field_ExternalClusterStrain,  // PhysicsType
			nullptr,                                   // MetaData
			RadialFalloff                              // FieldNode
		);
	}
}

void AChaosForceField::EnableChaosDestroy_Implementation()
{
	// Enable ticking to apply force field
	SetActorTickEnabled(true);
}

void AChaosForceField::DisableChaosDestroy_Implementation()
{
	// Disable ticking to stop applying force field
	SetActorTickEnabled(false);

	// Clear any existing field
	if (FieldSystemComponent)
	{
		FieldSystemComponent->ApplyPhysicsField(
			true,
			EFieldPhysicsType::Field_None,
			nullptr,
			nullptr
		);
	}
}
