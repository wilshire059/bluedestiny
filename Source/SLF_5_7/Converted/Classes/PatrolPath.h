// Copyright Epic Games, Inc. All Rights Reserved.
// Converted from Blueprint: B_PatrolPath

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SplineComponent.h"
#include "Components/ArrowComponent.h"
#include "PatrolPath.generated.h"

UCLASS(Blueprintable, BlueprintType)
class SLF_5_7_API APatrolPath : public AActor
{
	GENERATED_BODY()

public:
	APatrolPath();

protected:
	/** Spline component representing the patrol route */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USplineComponent> Route;

	/** Arrow component for direction visualization */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UArrowComponent> Arrow;

	/** Current point index on the patrol path */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Patrol")
	int32 CurrentPointIndex;

	/** Direction of travel along the patrol path (+1 or -1) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Patrol")
	int32 IncrementBy;

public:
	/** Set the next point index, automatically reversing at path ends */
	UFUNCTION(BlueprintCallable, Category = "Patrol")
	void SetNextPointIndex();

	/** Get the world position for the current patrol point */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Patrol")
	FVector GetWorldPositionForCurrentPoint() const;
};
