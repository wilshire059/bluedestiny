#include "BTS_IsTargetDead.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "AC_AI_BehaviorManager.h"
#include "AC_CombatManager.h"
#include "E_AI_States.h"
#include "StructUtils/InstancedStruct.h"

UBTS_IsTargetDead::UBTS_IsTargetDead()
{
	NodeName = TEXT("Is Target Dead");

	TargetKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTS_IsTargetDead, TargetKey), AActor::StaticClass());
}

void UBTS_IsTargetDead::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
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

	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (!BlackboardComp)
	{
		return;
	}

	// Get the target actor from blackboard
	AActor* TargetActor = Cast<AActor>(BlackboardComp->GetValueAsObject(TargetKey.SelectedKeyName));
	if (!TargetActor)
	{
		return;
	}

	// Get the target's combat manager to check if dead
	UAC_CombatManager* TargetCombatManager = TargetActor->FindComponentByClass<UAC_CombatManager>();
	if (!TargetCombatManager)
	{
		return;
	}

	// Check if target is dead
	bool bTargetIsDead = TargetCombatManager->bIsDead;

	if (bTargetIsDead)
	{
		// Get our behavior manager and switch to configured state (default: Investigating)
		UAC_AI_BehaviorManager* BehaviorManager = ControlledPawn->FindComponentByClass<UAC_AI_BehaviorManager>();
		if (BehaviorManager)
		{
			FInstancedStruct EmptyData;
			BehaviorManager->SetState(StateToSwitchTo, EmptyData);
		}
	}
}
