#include "B_AP_Fire.h"

UB_AP_Fire::UB_AP_Fire()
{
	StatTag = FGameplayTag::RequestGameplayTag(FName("SoulslikeFramework.Stat.Secondary.AttackPower.Fire"));
	MaxValue = 9999.0f;
}
