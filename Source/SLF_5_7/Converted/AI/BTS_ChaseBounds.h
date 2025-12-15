#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlueprintBase.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "BTS_ChaseBounds.generated.h"

UCLASS()
class SLF_5_7_API UBTS_ChaseBounds : public UBTService_BlueprintBase
{
	GENERATED_BODY()

public:
	UBTS_ChaseBounds();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackboard")
	FBlackboardKeySelector TargetKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackboard")
	FBlackboardKeySelector OutOfBoundsKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chase")
	float MaxChaseDistance = 2000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chase")
	bool bUseStartLocation = true;

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	FVector StartLocation;
	bool bStartLocationSet = false;
};
