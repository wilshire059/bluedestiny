#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AN_WorldCameraShake.generated.h"

class UCameraShakeBase;

UCLASS()
class SLF_5_7_API UAN_WorldCameraShake : public UAnimNotify
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CameraShake")
	TSubclassOf<UCameraShakeBase> CameraShakeClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CameraShake")
	float InnerRadius = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CameraShake")
	float OuterRadius = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CameraShake")
	float Falloff = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CameraShake")
	bool bOrientShakeTowardsEpicenter = true;

	virtual FString GetNotifyName_Implementation() const override;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};
