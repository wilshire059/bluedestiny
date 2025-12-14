#include "ABP_Quinn_PostProcess.h"
#include "GameFramework/Character.h"

void UABP_Quinn_PostProcess::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	OwnerCharacter = Cast<ACharacter>(TryGetPawnOwner());
}

void UABP_Quinn_PostProcess::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	// Post-process animation updates (IK, procedural adjustments)
	// would be implemented here
}
