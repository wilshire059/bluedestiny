#include "B_StatusEffect_Frostbite.h"

UB_StatusEffect_Frostbite::UB_StatusEffect_Frostbite()
{
	DamageNegationReduction = 0.20f;
}

void UB_StatusEffect_Frostbite::OnTriggered_Implementation()
{
	Super::OnTriggered_Implementation();
	// Reduce damage negation
}

void UB_StatusEffect_Frostbite::OnRemoved_Implementation()
{
	Super::OnRemoved_Implementation();
	// Restore damage negation
}
