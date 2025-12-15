#include "BTT_GetRandomPoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "NavigationSystem.h"

UBTT_GetRandomPoint::UBTT_GetRandomPoint()
{
	NodeName = TEXT("Get Random Point");

	TargetKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UBTT_GetRandomPoint, TargetKey));
}

EBTNodeResult::Type UBTT_GetRandomPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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

	FVector Origin = ControlledPawn->GetActorLocation();
	FNavLocation RandomLocation;

	UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(GetWorld());
	if (NavSys && NavSys->GetRandomReachablePointInRadius(Origin, Radius, RandomLocation))
	{
		BlackboardComp->SetValueAsVector(TargetKey.SelectedKeyName, RandomLocation.Location);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
