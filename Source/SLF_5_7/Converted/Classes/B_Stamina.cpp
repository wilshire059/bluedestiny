#include "B_Stamina.h"

UB_Stamina::UB_Stamina()
{
	StatTag = FGameplayTag::RequestGameplayTag(FName("SoulslikeFramework.Stat.Secondary.Stamina"));
	CurrentValue = 50.0f;
	MaxValue = 50.0f;
	RegenConfig.bCanRegenerate = true;
	RegenConfig.RegenPercent = 100.0f;
	RegenConfig.RegenInterval = 2.0f;
}
