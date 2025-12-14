#include "B_Dexterity.h"

UB_Dexterity::UB_Dexterity()
{
	StatTag = FGameplayTag::RequestGameplayTag(FName("SoulslikeFramework.Stat.Primary.Dexterity"));
	MaxValue = 99.0f;
}
