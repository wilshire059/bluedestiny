#include "BTT_GetCurrentLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

UBTT_GetCurrentLocation::UBTT_GetCurrentLocation()
{
	NodeName = TEXT("Get Current Location");

	LocationKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UBTT_GetCurrentLocation, LocationKey));
}

EBTNodeResult::Type UBTT_GetCurrentLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsVector(LocationKey.SelectedKeyName, ControlledPawn->GetActorLocation());
	}

	return EBTNodeResult::Succeeded;
}
