#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlueprintBase.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "Enums/E_AI_States.h"
#include "BTS_IsTargetDead.generated.h"

class UAC_AI_BehaviorManager;

UCLASS()
class SLF_5_7_API UBTS_IsTargetDead : public UBTService_BlueprintBase
{
	GENERATED_BODY()

public:
	UBTS_IsTargetDead();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackboard")
	FBlackboardKeySelector TargetKey;

	/** State to switch to when target is dead (default: Investigating per Blueprint) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	E_AI_States StateToSwitchTo = E_AI_States::Investigating;

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
