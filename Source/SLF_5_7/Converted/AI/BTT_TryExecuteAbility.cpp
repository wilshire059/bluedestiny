#include "BTT_TryExecuteAbility.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "AC_AI_CombatManager.h"

UBTT_TryExecuteAbility::UBTT_TryExecuteAbility()
{
	NodeName = TEXT("Try Execute Ability");

	AbilityKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTT_TryExecuteAbility, AbilityKey), UObject::StaticClass());
}

EBTNodeResult::Type UBTT_TryExecuteAbility::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController)
	{
		return EBTNodeResult::Failed;
	}

	APawn* ControlledPawn = AIController->GetPawn();
	if (!ControlledPawn)
	{
		return EBTNodeResult::Failed;
	}

	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (!BlackboardComp)
	{
		return EBTNodeResult::Failed;
	}

	// Get ability from blackboard
	UObject* Ability = BlackboardComp->GetValueAsObject(AbilityKey.SelectedKeyName);
	if (!Ability)
	{
		return EBTNodeResult::Failed;
	}

	// Get combat manager component
	UAC_AI_CombatManager* CombatManager = ControlledPawn->FindComponentByClass<UAC_AI_CombatManager>();
	if (!CombatManager)
	{
		return EBTNodeResult::Failed;
	}

	// Execute the ability
	bool bSuccess = CombatManager->ExecuteAbility(Ability);

	// Clear the ability key after use
	BlackboardComp->ClearValue(AbilityKey.SelectedKeyName);

	return bSuccess ? EBTNodeResult::Succeeded : EBTNodeResult::Failed;
}
