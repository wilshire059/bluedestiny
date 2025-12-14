#include "B_Buff.h"

UB_Buff::UB_Buff()
{
	Rank = 1;
	RemainingDuration = 0.0f;
}

void UB_Buff::OnGranted_Implementation()
{
	// Override in subclasses
}

void UB_Buff::OnRemoved_Implementation()
{
	// Override in subclasses
}

void UB_Buff::OnTick_Implementation(float DeltaTime)
{
	RemainingDuration -= DeltaTime;
}
