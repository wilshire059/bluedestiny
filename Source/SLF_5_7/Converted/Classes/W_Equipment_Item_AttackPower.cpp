#include "W_Equipment_Item_AttackPower.h"

void UW_Equipment_Item_AttackPower::SetupAttackPowerStats(const TMap<FGameplayTag, int32>& TargetAttackPowerStats,
	const TMap<FGameplayTag, int32>& CurrentAttackPowerStats, bool bCanCompare)
{
	OnSetupAttackPowerStats(TargetAttackPowerStats, CurrentAttackPowerStats, bCanCompare);
}
