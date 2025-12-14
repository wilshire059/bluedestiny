#include "W_Equipment_Item_RequiredStats.h"

void UW_Equipment_Item_RequiredStats::SetupRequiredStats(const TMap<FGameplayTag, int32>& RequiredStats,
	const TMap<FGameplayTag, int32>& CurrentStats)
{
	OnSetupRequiredStats(RequiredStats, CurrentStats);
}
