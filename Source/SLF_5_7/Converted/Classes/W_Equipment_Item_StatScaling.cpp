#include "W_Equipment_Item_StatScaling.h"

void UW_Equipment_Item_StatScaling::SetupStatScaling(const TMap<FGameplayTag, E_StatScaling>& StatScaling)
{
	OnSetupStatScaling(StatScaling);
}
