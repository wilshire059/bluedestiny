#include "ABP_SoulslikeNPC.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void UABP_SoulslikeNPC::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	OwnerCharacter = Cast<ACharacter>(TryGetPawnOwner());
	if (OwnerCharacter)
	{
		MovementComponent = OwnerCharacter->GetCharacterMovement();
	}
}

void UABP_SoulslikeNPC::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!OwnerCharacter || !MovementComponent)
	{
		return;
	}

	Speed = MovementComponent->Velocity.Size2D();
	bIsMoving = Speed > 10.0f;
}
