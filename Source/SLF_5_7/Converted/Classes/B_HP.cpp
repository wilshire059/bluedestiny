#include "B_HP.h"

UB_HP::UB_HP()
{
	StatTag = FGameplayTag::RequestGameplayTag(FName("SoulslikeFramework.Stat.Secondary.HP"));
	CurrentValue = 500.0f;
	MaxValue = 500.0f;
}
