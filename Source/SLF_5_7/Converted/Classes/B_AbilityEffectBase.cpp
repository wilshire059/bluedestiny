#include "B_AbilityEffectBase.h"

AB_AbilityEffectBase::AB_AbilityEffectBase()
{
	PrimaryActorTick.bCanEverTick = false;
	Duration = 0.0f;
	bDestroyOnComplete = true;
}

void AB_AbilityEffectBase::BeginPlay()
{
	Super::BeginPlay();
}

void AB_AbilityEffectBase::ActivateEffect_Implementation()
{
	// Override in subclasses
}

void AB_AbilityEffectBase::DeactivateEffect_Implementation()
{
	if (bDestroyOnComplete)
	{
		Destroy();
	}
}
