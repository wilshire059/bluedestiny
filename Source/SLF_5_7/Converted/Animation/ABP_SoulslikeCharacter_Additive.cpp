#include "ABP_SoulslikeCharacter_Additive.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void UABP_SoulslikeCharacter_Additive::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	OwnerCharacter = Cast<ACharacter>(TryGetPawnOwner());
	if (OwnerCharacter)
	{
		MovementComponent = OwnerCharacter->GetCharacterMovement();
	}
}

void UABP_SoulslikeCharacter_Additive::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!OwnerCharacter)
	{
		return;
	}

	// Update aim angles
	FRotator AimRotation = OwnerCharacter->GetControlRotation();
	FRotator ActorRotation = OwnerCharacter->GetActorRotation();
	FRotator DeltaRotation = (AimRotation - ActorRotation).GetNormalized();

	AimPitch = DeltaRotation.Pitch;
	AimYaw = DeltaRotation.Yaw;

	// Calculate lean based on velocity
	if (MovementComponent)
	{
		FVector Velocity = MovementComponent->Velocity;
		FVector RightVector = OwnerCharacter->GetActorRightVector();
		LeanAmount = FVector::DotProduct(Velocity.GetSafeNormal(), RightVector) * Velocity.Size() / MovementComponent->MaxWalkSpeed;
	}
}
