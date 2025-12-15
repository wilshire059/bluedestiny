#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlueprintBase.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "BTS_DistanceCheck.generated.h"

UENUM(BlueprintType)
enum class ECompareOperation : uint8
{
	Equal,
	Less,
	LessEqual,
	Greater,
	GreaterEqual
};

UCLASS()
class SLF_5_7_API UBTS_DistanceCheck : public UBTService_BlueprintBase
{
	GENERATED_BODY()

public:
	UBTS_DistanceCheck();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackboard")
	FBlackboardKeySelector TargetKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackboard")
	FBlackboardKeySelector DistanceKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackboard")
	FBlackboardKeySelector KeyToSet;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Compare")
	ECompareOperation CompareType = ECompareOperation::LessEqual;

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
