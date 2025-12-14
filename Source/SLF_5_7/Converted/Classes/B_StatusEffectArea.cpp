#include "B_StatusEffectArea.h"

AB_StatusEffectArea::AB_StatusEffectArea()
{
	PrimaryActorTick.bCanEverTick = true;
	Radius = 300.0f;
	BuildupPerSecond = 10.0f;
	Rank = 1;
}

void AB_StatusEffectArea::BeginPlay()
{
	Super::BeginPlay();
}

void AB_StatusEffectArea::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// Check for actors in radius and apply buildup
}
