#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlueprintBase.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "BTT_ClearKey.generated.h"

UCLASS()
class SLF_5_7_API UBTT_ClearKey : public UBTTask_BlueprintBase
{
	GENERATED_BODY()

public:
	UBTT_ClearKey();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackboard")
	FBlackboardKeySelector Key;

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
