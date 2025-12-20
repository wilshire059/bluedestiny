#include "BTS_ChaseBounds.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "AC_AI_BehaviorManager.h"
#include "E_AI_States.h"
#include "StructUtils/InstancedStruct.h"
#include "Kismet/KismetMathLibrary.h"

UBTS_ChaseBounds::UBTS_ChaseBounds()
{
	NodeName = TEXT("Chase Bounds");

	StartPositionKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UBTS_ChaseBounds, StartPositionKey));
	ChaseDistanceKey.AddFloatFilter(this, GET_MEMBER_NAME_CHECKED(UBTS_ChaseBounds, ChaseDistanceKey));
	StateKey.AddEnumFilter(this, GET_MEMBER_NAME_CHECKED(UBTS_ChaseBounds, StateKey), StaticEnum<E_AI_States>());
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

	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (!BlackboardComp)
	{
		return;
	}

	// Get start position from blackboard
	FVector StartPosition = BlackboardComp->GetValueAsVector(StartPositionKey.SelectedKeyName);

	// Get current pawn location
	FVector CurrentLocation = ControlledPawn->GetActorLocation();

	// Calculate distance from start position
	double Distance = UKismetMathLibrary::Vector_Distance(StartPosition, CurrentLocation);

	// Get chase distance threshold from blackboard
	float ChaseDistance = BlackboardComp->GetValueAsFloat(ChaseDistanceKey.SelectedKeyName);

	// Check if we've exceeded the chase bounds
	if (Distance > ChaseDistance)
	{
		// Get the state from blackboard and switch to it
		uint8 StateValue = BlackboardComp->GetValueAsEnum(StateKey.SelectedKeyName);
		E_AI_States NewState = static_cast<E_AI_States>(StateValue);

		// Get behavior manager and set new state
		UAC_AI_BehaviorManager* BehaviorManager = ControlledPawn->FindComponentByClass<UAC_AI_BehaviorManager>();
		if (BehaviorManager)
		{
			FInstancedStruct EmptyData;
			BehaviorManager->SetState(NewState, EmptyData);
		}
	}
}
