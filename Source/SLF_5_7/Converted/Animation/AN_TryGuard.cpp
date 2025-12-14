#include "AN_TryGuard.h"
#include "Interfaces/BPI_Generic_Character.h"

FString UAN_TryGuard::GetNotifyName_Implementation() const
{
	return TEXT("Try Guard");
}

void UAN_TryGuard::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (!MeshComp)
	{
		return;
	}

	AActor* Owner = MeshComp->GetOwner();
	if (Owner && Owner->Implements<UBPI_Generic_Character>())
	{
		// Try guard logic - call interface method
	}
}
