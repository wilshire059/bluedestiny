#include "W_Equipment_Item_StatsGranted.h"

void UW_Equipment_Item_StatsGranted::SetupStatsGranted(const TMap<FGameplayTag, int32>& StatsGranted)
{
	OnSetupStatsGranted(StatsGranted);
}
