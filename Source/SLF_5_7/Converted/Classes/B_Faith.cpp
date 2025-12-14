#include "B_Faith.h"

UB_Faith::UB_Faith()
{
	StatTag = FGameplayTag::RequestGameplayTag(FName("SoulslikeFramework.Stat.Primary.Faith"));
	MaxValue = 99.0f;
}
