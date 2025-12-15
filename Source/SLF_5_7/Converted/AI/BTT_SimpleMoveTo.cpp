#include "BTT_SimpleMoveTo.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Navigation/PathFollowingComponent.h"

UBTT_SimpleMoveTo::UBTT_SimpleMoveTo()
{
	NodeName = TEXT("Simple Move To");
	bNotifyTick = false;
	bCreateNodeInstance = true;

	TargetKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTT_SimpleMoveTo, TargetKey), AActor::StaticClass());
	TargetKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UBTT_SimpleMoveTo, TargetKey));
}

EBTNodeResult::Type UBTT_SimpleMoveTo::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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

	// Try to get target as Actor first
	AActor* TargetActor = Cast<AActor>(BlackboardComp->GetValueAsObject(TargetKey.SelectedKeyName));

	EPathFollowingRequestResult::Type MoveResult;

	if (TargetActor)
	{
		// Move to actor
		MoveResult = AIController->MoveToActor(TargetActor, AcceptanceRadius, bStopOnOverlap);
	}
	else
	{
		// Try to get target as Vector
		FVector TargetLocation = BlackboardComp->GetValueAsVector(TargetKey.SelectedKeyName);
		MoveResult = AIController->MoveToLocation(TargetLocation, AcceptanceRadius, bStopOnOverlap);
	}

	if (MoveResult == EPathFollowingRequestResult::RequestSuccessful)
	{
		return EBTNodeResult::InProgress;
	}
	else if (MoveResult == EPathFollowingRequestResult::AlreadyAtGoal)
	{
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}

EBTNodeResult::Type UBTT_SimpleMoveTo::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (AIController)
	{
		AIController->StopMovement();
	}

	return EBTNodeResult::Aborted;
}
