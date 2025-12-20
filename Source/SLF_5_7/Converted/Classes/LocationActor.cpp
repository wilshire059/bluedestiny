// Copyright Epic Games, Inc. All Rights Reserved.
// Converted from Blueprint: B_LocationActor

#include "LocationActor.h"

ALocationActor::ALocationActor()
{
	// Set this actor to call Tick() every frame - not needed for location actor
	PrimaryActorTick.bCanEverTick = false;

	// Create default scene root
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;

	// Create arrow component for direction visualization
	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Arrow->SetupAttachment(RootComponent);

	// Create billboard component for editor visualization
	Billboard = CreateDefaultSubobject<UBillboardComponent>(TEXT("Billboard"));
	Billboard->SetupAttachment(RootComponent);
}
