// Copyright 2025. Wilshire. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_ClearKey.generated.h"

/**
 * Behavior Tree Task: Clears a specified blackboard key
 */
UCLASS()
class SLF_5_7_API UBTT_ClearKey : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTT_ClearKey();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector Key;
};
