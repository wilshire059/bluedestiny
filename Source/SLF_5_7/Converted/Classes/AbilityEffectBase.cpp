// Copyright Epic Games, Inc. All Rights Reserved.
// Converted from Blueprint: B_AbilityEffectBase

#include "AbilityEffectBase.h"
#include "Kismet/KismetSystemLibrary.h"

AAbilityEffectBase::AAbilityEffectBase()
{
	PrimaryActorTick.bCanEverTick = false;

	// Create default scene root
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;
}

void AAbilityEffectBase::BeginPlay()
{
	Super::BeginPlay();

	// Print debug text
	FText DebugText = FText::Format(
		FText::FromString(TEXT("Ability Effect \"{0}\" spawned.")),
		FText::FromString(GetName())
	);

	UKismetSystemLibrary::PrintText(
		this,
		DebugText,
		true,  // PrintToScreen
		true,  // PrintToLog
		FLinearColor(0.0f, 0.66f, 1.0f, 1.0f),  // TextColor
		2.0f   // Duration
	);

	// Destroy self immediately
	K2_DestroyActor();
}
