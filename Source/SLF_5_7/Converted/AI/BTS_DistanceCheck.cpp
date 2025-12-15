#include "BTS_DistanceCheck.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

UBTS_DistanceCheck::UBTS_DistanceCheck()
{
	NodeName = TEXT("Distance Check");

	TargetKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTS_DistanceCheck, TargetKey), AActor::StaticClass());
	DistanceKey.AddFloatFilter(this, GET_MEMBER_NAME_CHECKED(UBTS_DistanceCheck, DistanceKey));
	KeyToSet.AddBoolFilter(this, GET_MEMBER_NAME_CHECKED(UBTS_DistanceCheck, KeyToSet));
}

void UBTS_DistanceCheck::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
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

	AActor* TargetActor = Cast<AActor>(BlackboardComp->GetValueAsObject(TargetKey.SelectedKeyName));
	if (!TargetActor)
	{
		return;
	}

	float Distance = ControlledPawn->GetDistanceTo(TargetActor);
	float CompareDistance = BlackboardComp->GetValueAsFloat(DistanceKey.SelectedKeyName);

	bool bResult = false;
	switch (CompareType)
	{
	case ECompareOperation::Equal:
		bResult = FMath::IsNearlyEqual(Distance, CompareDistance);
		break;
	case ECompareOperation::Less:
		bResult = Distance < CompareDistance;
		break;
	case ECompareOperation::LessEqual:
		bResult = Distance <= CompareDistance;
		break;
	case ECompareOperation::Greater:
		bResult = Distance > CompareDistance;
		break;
	case ECompareOperation::GreaterEqual:
		bResult = Distance >= CompareDistance;
		break;
	}

	BlackboardComp->SetValueAsBool(KeyToSet.SelectedKeyName, bResult);
}
