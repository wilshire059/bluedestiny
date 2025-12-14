#include "ANS_HyperArmor.h"
#include "Interfaces/BPI_Generic_Character.h"

FString UANS_HyperArmor::GetNotifyName_Implementation() const
{
	return TEXT("Hyper Armor");
}

void UANS_HyperArmor::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	if (!MeshComp)
	{
		return;
	}

	AActor* Owner = MeshComp->GetOwner();
	if (Owner && Owner->Implements<UBPI_Generic_Character>())
	{
		// Enable hyper armor state
	}
}

void UANS_HyperArmor::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	if (!MeshComp)
	{
		return;
	}

	AActor* Owner = MeshComp->GetOwner();
	if (Owner && Owner->Implements<UBPI_Generic_Character>())
	{
		// Disable hyper armor state
	}
}
