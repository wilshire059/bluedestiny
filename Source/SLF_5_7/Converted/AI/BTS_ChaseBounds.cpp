#include "BTS_ChaseBounds.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"

UBTS_ChaseBounds::UBTS_ChaseBounds()
{
	NodeName = TEXT("Chase Bounds");

	TargetKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTS_ChaseBounds, TargetKey), AActor::StaticClass());
	OutOfBoundsKey.AddBoolFilter(this, GET_MEMBER_NAME_CHECKED(UBTS_ChaseBounds, OutOfBoundsKey));
}

void UBTS_ChaseBounds::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
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

	// Set start location on first tick
	if (!bStartLocationSet && bUseStartLocation)
	{
		StartLocation = ControlledPawn->GetActorLocation();
		bStartLocationSet = true;
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

	// Calculate distance from start location to current position
	FVector ReferenceLocation = bUseStartLocation ? StartLocation : ControlledPawn->GetActorLocation();
	float DistanceToTarget = FVector::Dist(ReferenceLocation, TargetActor->GetActorLocation());

	// Check if out of bounds
	bool bOutOfBounds = DistanceToTarget > MaxChaseDistance;
	BlackboardComp->SetValueAsBool(OutOfBoundsKey.SelectedKeyName, bOutOfBounds);
}
