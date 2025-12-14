#pragma once

#include "CoreMinimal.h"
#include "ABP_SoulslikeEnemy.h"
#include "ABP_SoulslikeBossNew.generated.h"

UCLASS()
class SLF_5_7_API UABP_SoulslikeBossNew : public UABP_SoulslikeEnemy
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	// Boss-specific properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boss")
	int32 CurrentPhase = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boss")
	bool bIsEnraged = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boss")
	bool bIsTransitioning = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boss")
	float HealthPercent = 1.0f;
};
