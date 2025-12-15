#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlueprintBase.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "E_AI_States.h"
#include "BTT_SwitchState.generated.h"

UCLASS()
class SLF_5_7_API UBTT_SwitchState : public UBTTask_BlueprintBase
{
	GENERATED_BODY()

public:
	UBTT_SwitchState();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackboard")
	FBlackboardKeySelector CurrentStateKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackboard")
	FBlackboardKeySelector PreviousStateKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	E_AI_States NewState = E_AI_States::Idle;

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
