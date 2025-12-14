#include "B_Discovery.h"

UB_Discovery::UB_Discovery()
{
	StatTag = FGameplayTag::RequestGameplayTag(FName("SoulslikeFramework.Stat.Secondary.Discovery"));
	MaxValue = 9999.0f;
}
