#include "W_ItemInfoEntry_StatScaling.h"

void UW_ItemInfoEntry_StatScaling::SetupStatScaling(const TMap<FGameplayTag, E_StatScaling>& StatScaling)
{
	OnSetupStatScaling(StatScaling);
}
