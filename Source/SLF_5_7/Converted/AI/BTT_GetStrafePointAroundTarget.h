#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlueprintBase.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "BTT_GetStrafePointAroundTarget.generated.h"

UCLASS()
class SLF_5_7_API UBTT_GetStrafePointAroundTarget : public UBTTask_BlueprintBase
{
	GENERATED_BODY()

public:
	UBTT_GetStrafePointAroundTarget();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackboard")
	FBlackboardKeySelector TargetKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackboard")
	FBlackboardKeySelector OutputLocationKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Strafe")
	float MinDistance = 200.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Strafe")
	float MaxDistance = 400.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Strafe")
	float AngleRange = 90.0f;

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
