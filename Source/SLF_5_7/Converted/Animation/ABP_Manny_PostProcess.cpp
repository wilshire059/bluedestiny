#include "ABP_Manny_PostProcess.h"
#include "GameFramework/Character.h"

void UABP_Manny_PostProcess::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	OwnerCharacter = Cast<ACharacter>(TryGetPawnOwner());
}

void UABP_Manny_PostProcess::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	// Post-process animation updates (IK, procedural adjustments)
	// would be implemented here
}
