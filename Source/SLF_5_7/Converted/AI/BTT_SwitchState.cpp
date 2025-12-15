#include "BTT_SwitchState.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTT_SwitchState::UBTT_SwitchState()
{
	NodeName = TEXT("Switch State");

	CurrentStateKey.AddEnumFilter(this, GET_MEMBER_NAME_CHECKED(UBTT_SwitchState, CurrentStateKey), StaticEnum<E_AI_States>());
	PreviousStateKey.AddEnumFilter(this, GET_MEMBER_NAME_CHECKED(UBTT_SwitchState, PreviousStateKey), StaticEnum<E_AI_States>());
}

EBTNodeResult::Type UBTT_SwitchState::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (!BlackboardComp)
	{
		return EBTNodeResult::Failed;
	}

	// Store current state as previous
	uint8 CurrentState = BlackboardComp->GetValueAsEnum(CurrentStateKey.SelectedKeyName);
	BlackboardComp->SetValueAsEnum(PreviousStateKey.SelectedKeyName, CurrentState);

	// Set new state
	BlackboardComp->SetValueAsEnum(CurrentStateKey.SelectedKeyName, static_cast<uint8>(NewState));

	return EBTNodeResult::Succeeded;
}
