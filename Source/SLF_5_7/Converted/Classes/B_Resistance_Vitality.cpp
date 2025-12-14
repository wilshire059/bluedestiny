#include "B_Resistance_Vitality.h"

UB_Resistance_Vitality::UB_Resistance_Vitality()
{
	StatTag = FGameplayTag::RequestGameplayTag(FName("SoulslikeFramework.Stat.Defense.Resistances.Vitality"));
	MaxValue = 9999.0f;
}
