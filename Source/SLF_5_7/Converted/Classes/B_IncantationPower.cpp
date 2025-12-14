#include "B_IncantationPower.h"

UB_IncantationPower::UB_IncantationPower()
{
	StatTag = FGameplayTag::RequestGameplayTag(FName("SoulslikeFramework.Stat.Secondary.IncantationPower"));
	MaxValue = 9999.0f;
}
