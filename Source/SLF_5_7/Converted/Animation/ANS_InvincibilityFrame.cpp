#include "ANS_InvincibilityFrame.h"
#include "Interfaces/BPI_Generic_Character.h"

FString UANS_InvincibilityFrame::GetNotifyName_Implementation() const
{
	return TEXT("I-Frame");
}

void UANS_InvincibilityFrame::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	if (!MeshComp)
	{
		return;
	}

	AActor* Owner = MeshComp->GetOwner();
	if (Owner && Owner->Implements<UBPI_Generic_Character>())
	{
		// Enable invincibility frames
	}
}

void UANS_InvincibilityFrame::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	if (!MeshComp)
	{
		return;
	}

	AActor* Owner = MeshComp->GetOwner();
	if (Owner && Owner->Implements<UBPI_Generic_Character>())
	{
		// Disable invincibility frames
	}
}
