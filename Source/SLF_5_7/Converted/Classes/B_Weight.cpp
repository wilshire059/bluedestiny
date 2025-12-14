#include "B_Weight.h"

UB_Weight::UB_Weight()
{
	StatTag = FGameplayTag::RequestGameplayTag(FName("SoulslikeFramework.Stat.Secondary.Weight"));
	MaxValue = 9999.0f;
}
