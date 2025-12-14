#include "B_Strength.h"

UB_Strength::UB_Strength()
{
	StatTag = FGameplayTag::RequestGameplayTag(FName("SoulslikeFramework.Stat.Primary.Strength"));
	MaxValue = 99.0f;
}
