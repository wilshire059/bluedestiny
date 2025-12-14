#include "ANS_RegisterAttackSequence.h"
#include "Interfaces/BPI_Generic_Character.h"

FString UANS_RegisterAttackSequence::GetNotifyName_Implementation() const
{
	return TEXT("Attack Sequence");
}

void UANS_RegisterAttackSequence::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	if (!MeshComp)
	{
		return;
	}

	AActor* Owner = MeshComp->GetOwner();
	if (Owner && Owner->Implements<UBPI_Generic_Character>())
	{
		// Register attack sequence for combo tracking
	}
}

void UANS_RegisterAttackSequence::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	// End of attack sequence window
}
