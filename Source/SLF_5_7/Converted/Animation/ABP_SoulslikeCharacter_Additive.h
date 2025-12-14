#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Interfaces/ALI_LocomotionStates.h"
#include "Interfaces/ALI_OverlayStates.h"
#include "ABP_SoulslikeCharacter_Additive.generated.h"

UCLASS()
class SLF_5_7_API UABP_SoulslikeCharacter_Additive : public UAnimInstance, public IALI_LocomotionStates, public IALI_OverlayStates
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	// Additive animation properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Additive")
	float LeanAmount = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Additive")
	float AimPitch = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Additive")
	float AimYaw = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Additive")
	bool bIsAiming = false;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "References")
	TObjectPtr<class ACharacter> OwnerCharacter;

	UPROPERTY(BlueprintReadOnly, Category = "References")
	TObjectPtr<class UCharacterMovementComponent> MovementComponent;
};
