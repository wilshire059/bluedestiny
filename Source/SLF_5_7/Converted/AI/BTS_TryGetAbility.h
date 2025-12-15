#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlueprintBase.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "BTS_TryGetAbility.generated.h"

class UAC_AI_CombatManager;

UCLASS()
class SLF_5_7_API UBTS_TryGetAbility : public UBTService_BlueprintBase
{
	GENERATED_BODY()

public:
	UBTS_TryGetAbility();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackboard")
	FBlackboardKeySelector AbilityKey;

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
