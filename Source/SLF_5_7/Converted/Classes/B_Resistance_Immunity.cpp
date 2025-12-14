#include "B_Resistance_Immunity.h"

UB_Resistance_Immunity::UB_Resistance_Immunity()
{
	StatTag = FGameplayTag::RequestGameplayTag(FName("SoulslikeFramework.Stat.Defense.Resistances.Immunity"));
	MaxValue = 9999.0f;
}
