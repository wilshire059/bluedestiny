#include "B_Buff_AttackPower.h"

UB_Buff_AttackPower::UB_Buff_AttackPower()
{
	AttackPowerBonus = 0.0f;
}

void UB_Buff_AttackPower::OnGranted_Implementation()
{
	Super::OnGranted_Implementation();
	// Apply attack power bonus
}

void UB_Buff_AttackPower::OnRemoved_Implementation()
{
	Super::OnRemoved_Implementation();
	// Remove attack power bonus
}
