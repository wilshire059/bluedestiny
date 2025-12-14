#include "B_DN_Physical.h"

UB_DN_Physical::UB_DN_Physical()
{
	StatTag = FGameplayTag::RequestGameplayTag(FName("SoulslikeFramework.Stat.Defense.Negation.Physical"));
	MaxValue = 9999.0f;
}
