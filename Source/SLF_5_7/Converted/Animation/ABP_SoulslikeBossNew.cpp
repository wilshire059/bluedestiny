#include "ABP_SoulslikeBossNew.h"

void UABP_SoulslikeBossNew::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UABP_SoulslikeBossNew::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	// Boss-specific animation updates would go here
	// Typically involves checking boss phase and enrage state
}
