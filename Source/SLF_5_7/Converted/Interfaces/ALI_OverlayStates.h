#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimLayerInterface.h"
#include "ALI_OverlayStates.generated.h"

UINTERFACE(Blueprintable)
class SLF_5_7_API UALI_OverlayStates : public UAnimLayerInterface
{
	GENERATED_BODY()
};

class SLF_5_7_API IALI_OverlayStates : public IAnimLayerInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Overlay States")
	FPoseLink LL_TwoHanded_Right(FPoseLink Locomotion);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Overlay States")
	FPoseLink LL_Shield_Block_Right(FPoseLink InPose);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Overlay States")
	FPoseLink LL_Shield_Right(FPoseLink Locomotion);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Overlay States")
	FPoseLink LL_OneHanded_Right(FPoseLink Locomotion);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Overlay States")
	FPoseLink LL_TwoHanded_Left(FPoseLink Locomotion);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Overlay States")
	FPoseLink LL_Shield_Block_Left(FPoseLink InPose);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Overlay States")
	FPoseLink LL_Shield_Left(FPoseLink Locomotion);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Overlay States")
	FPoseLink LL_OneHanded_Left(FPoseLink Locomotion);
};
