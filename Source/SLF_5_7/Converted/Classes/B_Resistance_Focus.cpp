#include "B_Resistance_Focus.h"

UB_Resistance_Focus::UB_Resistance_Focus()
{
	StatTag = FGameplayTag::RequestGameplayTag(FName("SoulslikeFramework.Stat.Defense.Resistances.Focus"));
	MaxValue = 9999.0f;
}
