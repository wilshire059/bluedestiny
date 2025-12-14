#include "PDA_StatusEffect.h"

UPDA_StatusEffect::UPDA_StatusEffect()
{
	BaseBuildupRate = 1.0;
	BaseDecayRate = 1.0;
	DecayDelay = 2.0;
	BarFillColor = FLinearColor::Black;
	bCanRetrigger = false;
}
