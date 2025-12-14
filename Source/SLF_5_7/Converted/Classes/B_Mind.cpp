#include "B_Mind.h"

UB_Mind::UB_Mind()
{
	StatTag = FGameplayTag::RequestGameplayTag(FName("SoulslikeFramework.Stat.Primary.Mind"));
	MaxValue = 99.0f;
}
