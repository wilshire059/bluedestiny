#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlueprintBase.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "BTS_SetMovementModeBasedOnDistance.generated.h"

UCLASS()
class SLF_5_7_API UBTS_SetMovementModeBasedOnDistance : public UBTService_BlueprintBase
{
	GENERATED_BODY()

public:
	UBTS_SetMovementModeBasedOnDistance();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackboard")
	FBlackboardKeySelector TargetKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackboard")
	FBlackboardKeySelector DistanceKey;

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
