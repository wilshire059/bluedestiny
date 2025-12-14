#include "B_AP_Magic.h"

UB_AP_Magic::UB_AP_Magic()
{
	StatTag = FGameplayTag::RequestGameplayTag(FName("SoulslikeFramework.Stat.Secondary.AttackPower.Magic"));
	MaxValue = 9999.0f;
}
