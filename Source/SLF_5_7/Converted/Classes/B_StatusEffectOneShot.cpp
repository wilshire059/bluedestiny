#include "B_StatusEffectOneShot.h"

AB_StatusEffectOneShot::AB_StatusEffectOneShot()
{
	PrimaryActorTick.bCanEverTick = false;
	Rank = 1;
}

void AB_StatusEffectOneShot::BeginPlay()
{
	Super::BeginPlay();
}

void AB_StatusEffectOneShot::TriggerOnActor(AActor* TargetActor)
{
	if (!TargetActor || !StatusEffect) return;
	// Immediately trigger the status effect on target
}
