#include "BTT_SetMovementMode.h"
#include "AIController.h"
#include "BPI_Generic_Character.h"

UBTT_SetMovementMode::UBTT_SetMovementMode()
{
	NodeName = TEXT("Set Movement Mode");
}

EBTNodeResult::Type UBTT_SetMovementMode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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

	// Call interface method on controlled pawn
	if (ControlledPawn->GetClass()->ImplementsInterface(UBPI_Generic_Character::StaticClass()))
	{
		IBPI_Generic_Character::Execute_SetMovementMode(ControlledPawn, MovementType);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
