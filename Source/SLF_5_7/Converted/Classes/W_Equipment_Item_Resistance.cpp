#include "W_Equipment_Item_Resistance.h"

void UW_Equipment_Item_Resistance::SetupResistanceStats(const TMap<FGameplayTag, int32>& TargetResistanceStats,
	const TMap<FGameplayTag, int32>& CurrentResistanceStats, bool bCanCompare)
{
	OnSetupResistanceStats(TargetResistanceStats, CurrentResistanceStats, bCanCompare);
}
