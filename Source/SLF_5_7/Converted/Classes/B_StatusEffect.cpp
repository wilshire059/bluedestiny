#include "B_StatusEffect.h"

UB_StatusEffect::UB_StatusEffect()
{
	Rank = 1;
	CurrentBuildup = 0.0;
	MaxBuildup = 100.0;
	bIsActive = false;
}

void UB_StatusEffect::OnTriggered_Implementation()
{
	bIsActive = true;
}

void UB_StatusEffect::OnRemoved_Implementation()
{
	bIsActive = false;
	CurrentBuildup = 0.0;
}

void UB_StatusEffect::OnTick_Implementation(float DeltaTime)
{
	// Override in subclasses
}

void UB_StatusEffect::AddBuildup(double Amount)
{
	CurrentBuildup = FMath::Clamp(CurrentBuildup + Amount, 0.0, MaxBuildup);
	if (CurrentBuildup >= MaxBuildup && !bIsActive)
	{
		OnTriggered();
	}
}
