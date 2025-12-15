#include "BTT_GetRandomPointNearStartPosition.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"

UBTT_GetRandomPointNearStartPosition::UBTT_GetRandomPointNearStartPosition()
{
	NodeName = TEXT("Get Random Point Near Start Position");

	StartPositionKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UBTT_GetRandomPointNearStartPosition, StartPositionKey));
	TargetKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UBTT_GetRandomPointNearStartPosition, TargetKey));
}

EBTNodeResult::Type UBTT_GetRandomPointNearStartPosition::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (!BlackboardComp)
	{
		return EBTNodeResult::Failed;
	}

	FVector Origin = BlackboardComp->GetValueAsVector(StartPositionKey.SelectedKeyName);
	FNavLocation RandomLocation;

	UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(GetWorld());
	if (NavSys && NavSys->GetRandomReachablePointInRadius(Origin, Radius, RandomLocation))
	{
		BlackboardComp->SetValueAsVector(TargetKey.SelectedKeyName, RandomLocation.Location);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
