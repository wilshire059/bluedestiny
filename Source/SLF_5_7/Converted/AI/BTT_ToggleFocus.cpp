#include "BTT_ToggleFocus.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

UBTT_ToggleFocus::UBTT_ToggleFocus()
{
	NodeName = TEXT("Toggle Focus");

	TargetKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTT_ToggleFocus, TargetKey), AActor::StaticClass());
}

EBTNodeResult::Type UBTT_ToggleFocus::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController)
	{
		return EBTNodeResult::Failed;
	}

	if (bEnableFocus)
	{
		UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
		if (BlackboardComp)
		{
			AActor* TargetActor = Cast<AActor>(BlackboardComp->GetValueAsObject(TargetKey.SelectedKeyName));
			if (TargetActor)
			{
				AIController->SetFocus(TargetActor);
				return EBTNodeResult::Succeeded;
			}
		}
		return EBTNodeResult::Failed;
	}
	else
	{
		AIController->ClearFocus(EAIFocusPriority::Gameplay);
		return EBTNodeResult::Succeeded;
	}
}
