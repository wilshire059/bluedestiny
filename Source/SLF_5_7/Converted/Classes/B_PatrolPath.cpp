#include "Classes/B_PatrolPath.h"
#include "Components/SplineComponent.h"
#include "Components/ArrowComponent.h"

AB_PatrolPath::AB_PatrolPath()
{
    PrimaryActorTick.bCanEverTick = false;

    // Default Init from BP
    CurrentPointIndex = 0;
    IncrementBy = 1;

    // BP used Arrow as Root
    Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
    RootComponent = Arrow;
    Arrow->SetHiddenInGame(true);
    Arrow->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
    Arrow->SetCanEverAffectNavigation(false);

    Route = CreateDefaultSubobject<USplineComponent>(TEXT("Route"));
    Route->SetupAttachment(RootComponent);
    Route->SetHiddenInGame(false); // BP default: hidden in game = false (so debug lines show?) 
    // Actually BP 'Visible'=True, 'HiddenInGame'=False usually means visible in editor, hidden in game?
    // Let's check logic: if strictly following BP export:
    // Route Properties: HiddenInGame=False, Visible=True
    // Arrow Properties: HiddenInGame=True
}

void AB_PatrolPath::SetNextPointIndex()
{
    if (!Route) return;

    CurrentPointIndex += IncrementBy;

    const int32 NumPoints = Route->GetNumberOfSplinePoints();
    // Safety check if no points
    if (NumPoints < 2) 
    {
        CurrentPointIndex = 0;
        return; 
    }

    const int32 MaxIndex = NumPoints - 1;

    // Ping Pong Logic
    if (CurrentPointIndex >= MaxIndex)
    {
        CurrentPointIndex = MaxIndex;
        IncrementBy = -1;
    }
    else if (CurrentPointIndex <= 0)
    {
        CurrentPointIndex = 0;
        IncrementBy = 1;
    }
}

FVector AB_PatrolPath::GetWorldPositionForCurrentPoint() const
{
    if (!Route) return GetActorLocation();
    
    // Safety check just in case index is out of bounds due to editor changes
    const int32 NumPoints = Route->GetNumberOfSplinePoints();
    if (NumPoints == 0) return GetActorLocation();

    int32 SafeIndex = FMath::Clamp(CurrentPointIndex, 0, NumPoints - 1);
    
    return Route->GetLocationAtSplinePoint(SafeIndex, ESplineCoordinateSpace::World);
}
