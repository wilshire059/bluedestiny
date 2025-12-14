#include "AN_SetMovementMode.h"
#include "GameFramework/Character.h"

FString UAN_SetMovementMode::GetNotifyName_Implementation() const
{
	return TEXT("Set Movement Mode");
}

void UAN_SetMovementMode::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (!MeshComp)
	{
		return;
	}

	ACharacter* Character = Cast<ACharacter>(MeshComp->GetOwner());
	if (Character && Character->GetCharacterMovement())
	{
		Character->GetCharacterMovement()->SetMovementMode(MovementMode, CustomMode);
	}
}
