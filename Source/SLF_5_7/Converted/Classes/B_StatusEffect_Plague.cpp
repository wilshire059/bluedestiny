#include "B_StatusEffect_Plague.h"

UB_StatusEffect_Plague::UB_StatusEffect_Plague()
{
	PlagueDamagePercent = 0.25f;
}

void UB_StatusEffect_Plague::OnTriggered_Implementation()
{
	Super::OnTriggered_Implementation();
	// Apply instant plague damage
}
