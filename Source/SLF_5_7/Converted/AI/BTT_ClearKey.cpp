#include "BTT_ClearKey.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTT_ClearKey::UBTT_ClearKey()
{
	NodeName = TEXT("Clear Key");
}

EBTNodeResult::Type UBTT_ClearKey::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (BlackboardComp)
	{
		BlackboardComp->ClearValue(Key.SelectedKeyName);
	}

	return EBTNodeResult::Succeeded;
}
