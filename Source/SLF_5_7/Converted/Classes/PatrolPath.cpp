// Copyright Epic Games, Inc. All Rights Reserved.
// Converted from Blueprint: B_PatrolPath

#include "PatrolPath.h"

APatrolPath::APatrolPath()
{
	PrimaryActorTick.bCanEverTick = false;

	// Create route spline component
	Route = CreateDefaultSubobject<USplineComponent>(TEXT("Route"));
	RootComponent = Route;

	// Create arrow component for visualization
	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Arrow->SetupAttachment(RootComponent);

	// Initialize patrol variables
	CurrentPointIndex = 0;
	IncrementBy = 1;
}

void APatrolPath::SetNextPointIndex()
{
	// Add increment to current index
	CurrentPointIndex += IncrementBy;

	// Get number of spline points
	const int32 NumPoints = Route->GetNumberOfSplinePoints();

	// Check if we've reached the end of the path
	if (CurrentPointIndex >= NumPoints - 1)
	{
		// Reverse direction
		IncrementBy = -1;
	}
	// Check if we've reached the start of the path
	else if (CurrentPointIndex <= 0)
	{
		// Forward direction
		IncrementBy = 1;
	}
}

FVector APatrolPath::GetWorldPositionForCurrentPoint() const
{
	if (Route)
	{
		return Route->GetLocationAtSplinePoint(CurrentPointIndex, ESplineCoordinateSpace::World);
	}
	return FVector::ZeroVector;
}
