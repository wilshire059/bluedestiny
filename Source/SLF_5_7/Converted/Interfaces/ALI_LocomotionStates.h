#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimLayerInterface.h"
#include "ALI_LocomotionStates.generated.h"

UINTERFACE(Blueprintable)
class SLF_5_7_API UALI_LocomotionStates : public UAnimLayerInterface
{
	GENERATED_BODY()
};

class SLF_5_7_API IALI_LocomotionStates : public IAnimLayerInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Locomotion States")
	FPoseLink LL_RestingIdle();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Locomotion States")
	FPoseLink LL_CrouchCycle();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Locomotion States")
	FPoseLink LL_CrouchIdle();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Locomotion States")
	FPoseLink LL_Cycle();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Locomotion States")
	FPoseLink LL_Idle();
};
