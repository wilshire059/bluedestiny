#include "BTT_SwitchToPreviousState.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "E_AI_States.h"

UBTT_SwitchToPreviousState::UBTT_SwitchToPreviousState()
{
	NodeName = TEXT("Switch To Previous State");

	CurrentStateKey.AddEnumFilter(this, GET_MEMBER_NAME_CHECKED(UBTT_SwitchToPreviousState, CurrentStateKey), StaticEnum<E_AI_States>());
	PreviousStateKey.AddEnumFilter(this, GET_MEMBER_NAME_CHECKED(UBTT_SwitchToPreviousState, PreviousStateKey), StaticEnum<E_AI_States>());
}

EBTNodeResult::Type UBTT_SwitchToPreviousState::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (!BlackboardComp)
	{
		return EBTNodeResult::Failed;
	}

	// Get previous state
	uint8 PreviousState = BlackboardComp->GetValueAsEnum(PreviousStateKey.SelectedKeyName);
	uint8 CurrentState = BlackboardComp->GetValueAsEnum(CurrentStateKey.SelectedKeyName);

	// Swap states
	BlackboardComp->SetValueAsEnum(CurrentStateKey.SelectedKeyName, PreviousState);
	BlackboardComp->SetValueAsEnum(PreviousStateKey.SelectedKeyName, CurrentState);

	return EBTNodeResult::Succeeded;
}
