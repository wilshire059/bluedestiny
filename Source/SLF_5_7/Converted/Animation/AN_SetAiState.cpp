#include "AN_SetAiState.h"
#include "AIController.h"
#include "GameFramework/Pawn.h"

FString UAN_SetAiState::GetNotifyName_Implementation() const
{
	return TEXT("Set AI State");
}

void UAN_SetAiState::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (!MeshComp)
	{
		return;
	}

	APawn* Pawn = Cast<APawn>(MeshComp->GetOwner());
	if (Pawn)
	{
		AAIController* AIC = Cast<AAIController>(Pawn->GetController());
		if (AIC)
		{
			// Set AI state through interface or blackboard
		}
	}
}
