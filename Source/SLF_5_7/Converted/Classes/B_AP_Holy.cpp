#include "B_AP_Holy.h"

UB_AP_Holy::UB_AP_Holy()
{
	StatTag = FGameplayTag::RequestGameplayTag(FName("SoulslikeFramework.Stat.Secondary.AttackPower.Holy"));
	MaxValue = 9999.0f;
}
