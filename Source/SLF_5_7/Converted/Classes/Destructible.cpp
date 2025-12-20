// Copyright Epic Games, Inc. All Rights Reserved.
// Converted from Blueprint: B_Destructible

#include "Destructible.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/AssetManager.h"

ADestructible::ADestructible()
	: bSoundPlayed(false)
{
	PrimaryActorTick.bCanEverTick = false;

	// Create geometry collection component
	GC_DestructibleMesh = CreateDefaultSubobject<UGeometryCollectionComponent>(TEXT("GC_DestructibleMesh"));
	RootComponent = GC_DestructibleMesh;

	// Create billboard component for visualization
	Billboard = CreateDefaultSubobject<UBillboardComponent>(TEXT("Billboard"));
	Billboard->SetupAttachment(RootComponent);

	// Bind to the break event
	if (GC_DestructibleMesh)
	{
		GC_DestructibleMesh->OnChaosBreakEvent.AddDynamic(this, &ADestructible::OnChaosBreakEvent);
	}
}

void ADestructible::OnChaosBreakEvent(const FChaosBreakEvent& BreakEvent)
{
	// Do once - only play sound on first break
	if (bSoundPlayed)
	{
		return;
	}
	bSoundPlayed = true;

	// Check if we have a destruction sound to load
	if (DestructionSound.IsNull())
	{
		return;
	}

	// Async load the sound asset
	FStreamableManager& StreamableManager = UAssetManager::GetStreamableManager();
	TSharedPtr<FStreamableHandle> Handle = StreamableManager.RequestAsyncLoad(
		DestructionSound.ToSoftObjectPath(),
		[this, Handle]()
		{
			OnDestructionSoundLoaded(Handle);
		}
	);
}

void ADestructible::OnDestructionSoundLoaded(TSharedPtr<FStreamableHandle> Handle)
{
	if (!Handle.IsValid())
	{
		return;
	}

	// Get the loaded object
	UObject* LoadedObject = Handle->GetLoadedAsset();

	// Cast to SoundBase
	if (USoundBase* LoadedSound = Cast<USoundBase>(LoadedObject))
	{
		// Play sound at actor location
		UGameplayStatics::PlaySoundAtLocation(
			this,
			LoadedSound,
			GetActorLocation()
		);
	}
}
