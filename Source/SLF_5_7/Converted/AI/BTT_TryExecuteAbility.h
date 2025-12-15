#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlueprintBase.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "BTT_TryExecuteAbility.generated.h"

UCLASS()
class SLF_5_7_API UBTT_TryExecuteAbility : public UBTTask_BlueprintBase
{
	GENERATED_BODY()

public:
	UBTT_TryExecuteAbility();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackboard")
	FBlackboardKeySelector AbilityKey;

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
