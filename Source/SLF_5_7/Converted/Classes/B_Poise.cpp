#include "B_Poise.h"

UB_Poise::UB_Poise()
{
	StatTag = FGameplayTag::RequestGameplayTag(FName("SoulslikeFramework.Stat.Secondary.Poise"));
	MaxValue = 9999.0f;
}
