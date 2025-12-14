#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Interfaces/ALI_LocomotionStates.h"
#include "ABP_SoulslikeEnemy.generated.h"

UCLASS()
class SLF_5_7_API UABP_SoulslikeEnemy : public UAnimInstance, public IALI_LocomotionStates
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	// Movement properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float Speed = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float Direction = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	bool bIsMoving = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	bool bIsInAir = false;

	// Combat properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	bool bIsInCombat = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	bool bIsDead = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	bool bIsStaggered = false;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "References")
	TObjectPtr<class ACharacter> OwnerCharacter;

	UPROPERTY(BlueprintReadOnly, Category = "References")
	TObjectPtr<class UCharacterMovementComponent> MovementComponent;
};
