#include "BTS_TryGetAbility.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "AC_AI_CombatManager.h"

UBTS_TryGetAbility::UBTS_TryGetAbility()
{
	NodeName = TEXT("Try Get Ability");

	AbilityKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTS_TryGetAbility, AbilityKey), UObject::StaticClass());
}

void UBTS_TryGetAbility::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController)
	{
		return;
	}

	APawn* ControlledPawn = AIController->GetPawn();
	if (!ControlledPawn)
	{
		return;
	}

	// Get combat manager component
	UAC_AI_CombatManager* CombatManager = ControlledPawn->FindComponentByClass<UAC_AI_CombatManager>();
	if (!CombatManager)
	{
		return;
	}

	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (!BlackboardComp)
	{
		return;
	}

	// Try to get an ability from the combat manager
	UObject* Ability = CombatManager->TryGetAbility();
	if (Ability)
	{
		BlackboardComp->SetValueAsObject(AbilityKey.SelectedKeyName, Ability);
	}
}
