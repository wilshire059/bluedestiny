#include "BTT_PatrolPath.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "B_PatrolPath.h"

UBTT_PatrolPath::UBTT_PatrolPath()
{
	NodeName = TEXT("Patrol Path");

	PatrolPathKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTT_PatrolPath, PatrolPathKey), AActor::StaticClass());
	PatrolIndexKey.AddIntFilter(this, GET_MEMBER_NAME_CHECKED(UBTT_PatrolPath, PatrolIndexKey));
	TargetLocationKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UBTT_PatrolPath, TargetLocationKey));
}

EBTNodeResult::Type UBTT_PatrolPath::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (!BlackboardComp)
	{
		return EBTNodeResult::Failed;
	}

	AB_PatrolPath* PatrolPath = Cast<AB_PatrolPath>(BlackboardComp->GetValueAsObject(PatrolPathKey.SelectedKeyName));
	if (!PatrolPath)
	{
		return EBTNodeResult::Failed;
	}

	// Get current patrol point location
	FVector TargetLocation = PatrolPath->GetWorldPositionForCurrentPoint();
	BlackboardComp->SetValueAsVector(TargetLocationKey.SelectedKeyName, TargetLocation);

	// Move to next point for next iteration
	PatrolPath->SetNextPointIndex();

	return EBTNodeResult::Succeeded;
}
