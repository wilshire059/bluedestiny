#include "B_StatusEffect_Burn.h"

UB_StatusEffect_Burn::UB_StatusEffect_Burn()
{
	BurnDamagePerSecond = 5.0f;
	BurnDuration = 3.0f;
}

void UB_StatusEffect_Burn::OnTriggered_Implementation()
{
	Super::OnTriggered_Implementation();
	// Start burn damage over time
}

void UB_StatusEffect_Burn::OnTick_Implementation(float DeltaTime)
{
	Super::OnTick_Implementation(DeltaTime);
	if (bIsActive)
	{
		// Apply burn damage per tick
	}
}
