#include "B_AP_Physical.h"

UB_AP_Physical::UB_AP_Physical()
{
	StatTag = FGameplayTag::RequestGameplayTag(FName("SoulslikeFramework.Stat.Secondary.AttackPower.Physical"));
	MaxValue = 9999.0f;
}
