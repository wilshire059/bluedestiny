#include "W_Radar.h"
#include "Kismet/GameplayStatics.h"

void UW_Radar::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	UpdateRadar();
}

void UW_Radar::UpdateRadar()
{
	OnUpdateRadar();
}

FVector2D UW_Radar::WorldToRadarPosition(FVector WorldLocation) const
{
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	if (!PlayerPawn)
	{
		return FVector2D::ZeroVector;
	}

	FVector PlayerLocation = PlayerPawn->GetActorLocation();
	FVector Direction = WorldLocation - PlayerLocation;

	// Flatten to 2D
	FVector2D Direction2D(Direction.X, Direction.Y);
	float Distance = Direction2D.Size();

	// Normalize and scale to radar size
	if (Distance > 0.0f)
	{
		Direction2D.Normalize();
		float RadarDistance = FMath::Clamp(Distance / RadarRange, 0.0f, 1.0f) * (RadarSize * 0.5f);
		return Direction2D * RadarDistance;
	}

	return FVector2D::ZeroVector;
}
