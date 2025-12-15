#include "BTS_SetMovementModeBasedOnDistance.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "BPI_Generic_Character.h"
#include "E_MovementType.h"

UBTS_SetMovementModeBasedOnDistance::UBTS_SetMovementModeBasedOnDistance()
{
	NodeName = TEXT("Set Movement Mode Based On Distance");

	TargetKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTS_SetMovementModeBasedOnDistance, TargetKey), AActor::StaticClass());
	DistanceKey.AddFloatFilter(this, GET_MEMBER_NAME_CHECKED(UBTS_SetMovementModeBasedOnDistance, DistanceKey));
}

void UBTS_SetMovementModeBasedOnDistance::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
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
	float DistanceThreshold = BlackboardComp->GetValueAsFloat(DistanceKey.SelectedKeyName);

	// If distance > threshold, use Sprint, otherwise use Run
	E_MovementType MovementType = (Distance > DistanceThreshold) ? E_MovementType::Sprint : E_MovementType::Run;

	// Call interface method on controlled pawn
	if (ControlledPawn->GetClass()->ImplementsInterface(UBPI_Generic_Character::StaticClass()))
	{
		IBPI_Generic_Character::Execute_SetMovementMode(ControlledPawn, MovementType);
	}
}
