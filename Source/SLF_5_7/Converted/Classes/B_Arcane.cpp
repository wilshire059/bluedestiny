#include "B_Arcane.h"

UB_Arcane::UB_Arcane()
{
	StatTag = FGameplayTag::RequestGameplayTag(FName("SoulslikeFramework.Stat.Primary.Arcane"));
	MaxValue = 99.0f;
}
