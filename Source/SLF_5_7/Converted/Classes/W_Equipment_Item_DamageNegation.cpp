#include "W_Equipment_Item_DamageNegation.h"

void UW_Equipment_Item_DamageNegation::SetupDamageNegationStats(const TMap<FGameplayTag, int32>& TargetDamageNegationStats,
	const TMap<FGameplayTag, int32>& CurrentDamageNegationStats, bool bCanCompare)
{
	OnSetupDamageNegationStats(TargetDamageNegationStats, CurrentDamageNegationStats, bCanCompare);
}
