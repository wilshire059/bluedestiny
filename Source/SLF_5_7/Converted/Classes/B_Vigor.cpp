#include "B_Vigor.h"

UB_Vigor::UB_Vigor()
{
	StatTag = FGameplayTag::RequestGameplayTag(FName("SoulslikeFramework.Stat.Primary.Vigor"));
	MaxValue = 99.0f;
}
