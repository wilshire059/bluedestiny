#include "B_AP_Lightning.h"

UB_AP_Lightning::UB_AP_Lightning()
{
	StatTag = FGameplayTag::RequestGameplayTag(FName("SoulslikeFramework.Stat.Secondary.AttackPower.Lightning"));
	MaxValue = 9999.0f;
}
