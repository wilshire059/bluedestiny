#include "BTT_GetStrafePointAroundTarget.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "NavigationSystem.h"

UBTT_GetStrafePointAroundTarget::UBTT_GetStrafePointAroundTarget()
{
	NodeName = TEXT("Get Strafe Point Around Target");

	TargetKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTT_GetStrafePointAroundTarget, TargetKey), AActor::StaticClass());
	OutputLocationKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UBTT_GetStrafePointAroundTarget, OutputLocationKey));
}

EBTNodeResult::Type UBTT_GetStrafePointAroundTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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

	AActor* TargetActor = Cast<AActor>(BlackboardComp->GetValueAsObject(TargetKey.SelectedKeyName));
	if (!TargetActor)
	{
		return EBTNodeResult::Failed;
	}

	FVector TargetLocation = TargetActor->GetActorLocation();
	FVector PawnLocation = ControlledPawn->GetActorLocation();

	// Calculate direction from target to pawn
	FVector DirectionToPawn = (PawnLocation - TargetLocation).GetSafeNormal();

	// Random angle offset
	float RandomAngle = FMath::RandRange(-AngleRange, AngleRange);
	FRotator AngleRotation(0.0f, RandomAngle, 0.0f);
	FVector StrafeDirection = AngleRotation.RotateVector(DirectionToPawn);

	// Random distance
	float RandomDistance = FMath::RandRange(MinDistance, MaxDistance);

	// Calculate strafe point
	FVector StrafePoint = TargetLocation + (StrafeDirection * RandomDistance);

	// Project to navigation
	UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(GetWorld());
	if (NavSys)
	{
		FNavLocation ProjectedLocation;
		if (NavSys->ProjectPointToNavigation(StrafePoint, ProjectedLocation))
		{
			BlackboardComp->SetValueAsVector(OutputLocationKey.SelectedKeyName, ProjectedLocation.Location);
			return EBTNodeResult::Succeeded;
		}
	}

	// Fall back to unprojected point
	BlackboardComp->SetValueAsVector(OutputLocationKey.SelectedKeyName, StrafePoint);
	return EBTNodeResult::Succeeded;
}
