#include "B_StatusEffect_Bleed.h"

UB_StatusEffect_Bleed::UB_StatusEffect_Bleed()
{
	BleedDamagePercent = 0.15f;
}

void UB_StatusEffect_Bleed::OnTriggered_Implementation()
{
	Super::OnTriggered_Implementation();
	// Apply bleed damage as percent of max HP
}
