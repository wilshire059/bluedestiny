#include "ANS_InputBuffer.h"
#include "Interfaces/BPI_Generic_Character.h"

FString UANS_InputBuffer::GetNotifyName_Implementation() const
{
	return TEXT("Input Buffer");
}

void UANS_InputBuffer::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	if (!MeshComp)
	{
		return;
	}

	AActor* Owner = MeshComp->GetOwner();
	if (Owner && Owner->Implements<UBPI_Generic_Character>())
	{
		// Enable input buffer window
	}
}

void UANS_InputBuffer::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	if (!MeshComp)
	{
		return;
	}

	AActor* Owner = MeshComp->GetOwner();
	if (Owner && Owner->Implements<UBPI_Generic_Character>())
	{
		// Process buffered input and close window
	}
}
