// Copyright Epic Games, Inc. All Rights Reserved.
// Converted from Blueprint: B_Destructible

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GeometryCollection/GeometryCollectionComponent.h"
#include "Components/BillboardComponent.h"
#include "Sound/SoundBase.h"
#include "Engine/StreamableManager.h"
#include "Destructible.generated.h"

/**
 * Destructible actor using Geometry Collection for Chaos destruction
 * Plays a sound when the geometry breaks
 */
UCLASS(Blueprintable, BlueprintType)
class SLF_5_7_API ADestructible : public AActor
{
	GENERATED_BODY()

public:
	ADestructible();

protected:
	/** Geometry Collection component for Chaos destruction */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UGeometryCollectionComponent> GC_DestructibleMesh;

	/** Billboard component for editor visualization */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UBillboardComponent> Billboard;

	/** Geometry Collection asset */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Destruction")
	TObjectPtr<UGeometryCollection> GeometryCollection;

	/** Sound to play when the object is destroyed */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Destruction")
	TSoftObjectPtr<USoundBase> DestructionSound;

private:
	/** Called when the geometry collection breaks */
	UFUNCTION()
	void OnChaosBreakEvent(const FChaosBreakEvent& BreakEvent);

	/** Called when the destruction sound asset is loaded */
	void OnDestructionSoundLoaded(TSharedPtr<FStreamableHandle> Handle);

	/** Flag to ensure sound only plays once */
	bool bSoundPlayed;
};
