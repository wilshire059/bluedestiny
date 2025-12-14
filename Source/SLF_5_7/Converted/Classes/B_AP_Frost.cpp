#include "B_AP_Frost.h"

UB_AP_Frost::UB_AP_Frost()
{
	StatTag = FGameplayTag::RequestGameplayTag(FName("SoulslikeFramework.Stat.Secondary.AttackPower.Frost"));
	MaxValue = 9999.0f;
}
