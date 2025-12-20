// Copyright 2025. Wilshire. All Rights Reserved.

#include "BTT_ClearKey.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType.h"

UBTT_ClearKey::UBTT_ClearKey()
{
	NodeName = "Clear Key";
}

EBTNodeResult::Type UBTT_ClearKey::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (!BlackboardComp)
	{
		return EBTNodeResult::Failed;
	}

	BlackboardComp->ClearValue(Key.SelectedKeyName);

	return EBTNodeResult::Succeeded;
}
