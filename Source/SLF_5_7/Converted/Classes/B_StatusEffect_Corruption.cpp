#include "B_StatusEffect_Corruption.h"

UB_StatusEffect_Corruption::UB_StatusEffect_Corruption()
{
	FPDrainPerSecond = 5.0f;
}

void UB_StatusEffect_Corruption::OnTriggered_Implementation()
{
	Super::OnTriggered_Implementation();
}

void UB_StatusEffect_Corruption::OnTick_Implementation(float DeltaTime)
{
	Super::OnTick_Implementation(DeltaTime);
	if (bIsActive)
	{
		// Drain FP per tick
	}
}
