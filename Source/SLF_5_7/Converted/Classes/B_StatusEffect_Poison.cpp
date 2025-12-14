#include "B_StatusEffect_Poison.h"

UB_StatusEffect_Poison::UB_StatusEffect_Poison()
{
	PoisonDamagePerSecond = 3.0f;
	PoisonDuration = 10.0f;
}

void UB_StatusEffect_Poison::OnTriggered_Implementation()
{
	Super::OnTriggered_Implementation();
}

void UB_StatusEffect_Poison::OnTick_Implementation(float DeltaTime)
{
	Super::OnTick_Implementation(DeltaTime);
	if (bIsActive)
	{
		// Apply poison damage per tick
	}
}
