#include "B_StatusEffect_Madness.h"

UB_StatusEffect_Madness::UB_StatusEffect_Madness()
{
	MadnessDamagePercent = 0.20f;
	FPDamagePercent = 0.30f;
}

void UB_StatusEffect_Madness::OnTriggered_Implementation()
{
	Super::OnTriggered_Implementation();
	// Apply HP and FP damage as percent of max
}
