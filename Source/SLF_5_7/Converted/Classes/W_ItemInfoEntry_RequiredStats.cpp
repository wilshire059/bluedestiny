#include "W_ItemInfoEntry_RequiredStats.h"

void UW_ItemInfoEntry_RequiredStats::SetupRequiredStats(const TMap<FGameplayTag, int32>& RequiredStats, const TMap<FGameplayTag, int32>& CurrentStats)
{
	OnSetupRequiredStats(RequiredStats, CurrentStats);
}
