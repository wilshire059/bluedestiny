// Copyright Epic Games, Inc. All Rights Reserved.
// Converted from Blueprint: B_LocationActor

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayTagContainer.h"
#include "Components/ArrowComponent.h"
#include "Components/BillboardComponent.h"
#include "LocationActor.generated.h"

UCLASS(Blueprintable, BlueprintType)
class SLF_5_7_API ALocationActor : public AActor
{
	GENERATED_BODY()

public:
	ALocationActor();

protected:
	/** Root component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USceneComponent> DefaultSceneRoot;

	/** Arrow component for direction visualization */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UArrowComponent> Arrow;

	/** Billboard component for editor visualization */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UBillboardComponent> Billboard;

public:
	/** Location tag for identifying this location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Location")
	FGameplayTag LocationTag;
};
