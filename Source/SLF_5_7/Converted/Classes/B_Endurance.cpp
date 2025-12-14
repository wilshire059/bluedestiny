#include "B_Endurance.h"

UB_Endurance::UB_Endurance()
{
	StatTag = FGameplayTag::RequestGameplayTag(FName("SoulslikeFramework.Stat.Primary.Endurance"));
	MaxValue = 99.0f;
}
