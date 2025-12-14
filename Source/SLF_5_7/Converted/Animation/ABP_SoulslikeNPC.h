#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "ABP_SoulslikeNPC.generated.h"

UCLASS()
class SLF_5_7_API UABP_SoulslikeNPC : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	// NPC animation properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC")
	float Speed = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC")
	bool bIsMoving = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC")
	bool bIsTalking = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC")
	bool bIsInteracting = false;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "References")
	TObjectPtr<class ACharacter> OwnerCharacter;

	UPROPERTY(BlueprintReadOnly, Category = "References")
	TObjectPtr<class UCharacterMovementComponent> MovementComponent;
};
