#include "B_Resistance_Robustness.h"

UB_Resistance_Robustness::UB_Resistance_Robustness()
{
	StatTag = FGameplayTag::RequestGameplayTag(FName("SoulslikeFramework.Stat.Defense.Resistances.Robustness"));
	MaxValue = 9999.0f;
}
