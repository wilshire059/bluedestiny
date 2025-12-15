#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlueprintBase.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "BTT_SetKey.generated.h"

UENUM(BlueprintType)
enum class EBlackboardKeyType : uint8
{
	Bool,
	Int,
	Float,
	Vector,
	Object
};

UCLASS()
class SLF_5_7_API UBTT_SetKey : public UBTTask_BlueprintBase
{
	GENERATED_BODY()

public:
	UBTT_SetKey();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackboard")
	FBlackboardKeySelector Key;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Value")
	EBlackboardKeyType KeyType = EBlackboardKeyType::Bool;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Value", meta = (EditCondition = "KeyType == EBlackboardKeyType::Bool"))
	bool BoolValue = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Value", meta = (EditCondition = "KeyType == EBlackboardKeyType::Int"))
	int32 IntValue = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Value", meta = (EditCondition = "KeyType == EBlackboardKeyType::Float"))
	float FloatValue = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Value", meta = (EditCondition = "KeyType == EBlackboardKeyType::Vector"))
	FVector VectorValue = FVector::ZeroVector;

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
