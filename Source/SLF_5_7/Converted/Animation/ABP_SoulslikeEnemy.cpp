#include "ABP_SoulslikeEnemy.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UABP_SoulslikeEnemy::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	OwnerCharacter = Cast<ACharacter>(TryGetPawnOwner());
	if (OwnerCharacter)
	{
		MovementComponent = OwnerCharacter->GetCharacterMovement();
	}
}

void UABP_SoulslikeEnemy::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!OwnerCharacter || !MovementComponent)
	{
		return;
	}

	// Calculate speed and direction
	FVector Velocity = MovementComponent->Velocity;
	Speed = Velocity.Size2D();
	bIsMoving = Speed > 10.0f;

	// Calculate movement direction relative to actor rotation
	if (bIsMoving)
	{
		FRotator VelocityRotation = Velocity.ToOrientationRotator();
		FRotator ActorRotation = OwnerCharacter->GetActorRotation();
		Direction = UKismetMathLibrary::NormalizedDeltaRotator(VelocityRotation, ActorRotation).Yaw;
	}
	else
	{
		Direction = 0.0f;
	}

	// Check if in air
	bIsInAir = MovementComponent->IsFalling();
}
