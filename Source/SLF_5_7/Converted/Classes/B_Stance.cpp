#include "B_Stance.h"

UB_Stance::UB_Stance()
{
	StatTag = FGameplayTag::RequestGameplayTag(FName("SoulslikeFramework.Stat.Secondary.Stance"));
	MaxValue = 9999.0f;
}
