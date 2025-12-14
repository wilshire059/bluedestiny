#include "B_Intelligence.h"

UB_Intelligence::UB_Intelligence()
{
	StatTag = FGameplayTag::RequestGameplayTag(FName("SoulslikeFramework.Stat.Primary.Intelligence"));
	MaxValue = 99.0f;
}
