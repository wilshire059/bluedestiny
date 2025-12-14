#include "B_FP.h"

UB_FP::UB_FP()
{
	StatTag = FGameplayTag::RequestGameplayTag(FName("SoulslikeFramework.Stat.Secondary.FP"));
	CurrentValue = 100.0f;
	MaxValue = 100.0f;
}
