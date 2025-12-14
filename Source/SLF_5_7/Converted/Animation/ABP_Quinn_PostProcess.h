#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "ABP_Quinn_PostProcess.generated.h"

/**
 * Post-process Animation Blueprint for Quinn mannequin.
 * Used for procedural bone adjustments and IK.
 */
UCLASS()
class SLF_5_7_API UABP_Quinn_PostProcess : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	// IK properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IK")
	float FootIKAlpha = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IK")
	float HandIKAlpha = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IK")
	FVector LeftFootEffectorLocation = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IK")
	FVector RightFootEffectorLocation = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IK")
	float PelvisOffset = 0.0f;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "References")
	TObjectPtr<class ACharacter> OwnerCharacter;
};
