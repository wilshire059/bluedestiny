#include "B_StatusEffectBuildup.h"

AB_StatusEffectBuildup::AB_StatusEffectBuildup()
{
	PrimaryActorTick.bCanEverTick = false;
	BuildupAmount = 25.0f;
	Rank = 1;
}

void AB_StatusEffectBuildup::BeginPlay()
{
	Super::BeginPlay();
}

void AB_StatusEffectBuildup::ApplyToActor(AActor* TargetActor)
{
	if (!TargetActor || !StatusEffect) return;
	// Apply buildup to target's status effect manager
}
